
#include<iostream> 
#include<fstream> 
#include<string.h> 
#include<cstdlib>
#include<conio.h>
#include<regex>
#include<windows.h>
using namespace std;



void setColor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

class Dash;


class DupException
{
private:
    string message;
public:
    DupException(string msg) 
	{ 
		message = msg;
	}
    string getMessage() const 
	{ 
		return message; 
	}
};



bool checkOnlyNumbers(string text) {
    
    \
    if (text.length() != 10) {
        return false; 
    }
    
    
    for (int i = 0; i < text.length(); i++) {
        char singleLetter = text[i]; 
        
        
        if (singleLetter < '0' || singleLetter > '9') {
            return false; 
        }
       
    }

    return true; 
}

bool isValidCitizenNo(string text) {
    
   if (text.length() < 7 || text.length() > 16) {
        return false;
    }
    
   const regex citizenPattern(R"(^[0-9]+[-/][0-9]+[-/][0-9]+[-/]*[0-9]*$)");
    
    return regex_match(text, citizenPattern);
}


bool isValidEmail(const string email)
{
	const regex valid(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-]{2,}(\.[a-zA-Z]{2,6})?$)");
	return regex_match(email, valid);
}

bool checkOnlyLetters(string text) {
    
    if (text.length() == 0) {
        return false;
    }
    
    
    for (int i = 0; i < text.length(); i++) {
        char letter = text[i];
        
       
        if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z') && letter != ' ') {
            return false; 
        }
    }
    
    return true; 
}


string toLowerCase(string text) {
    for (int i = 0; i < text.length(); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = text[i] + 32; 
        }
    }
    return text;
}

string askAndValidateBirthday() 
{
    int day, month, year;
    setColor(14);
    cout << "\n\t--- Enter Birthday Components ---\n";
    
  
    while (true) {
    	setColor(10);
        cout << "\tEnter Day (1-31): ";
        setColor(7);
        if (cin >> day && day >= 1 && day <= 31) {
            cin.ignore(10000, '\n'); // Clear extra text trailing the valid number
            break; // Day is correct! Break out of the day loop and move down
        }
        setColor(12);
        cout << "\tError: Invalid day parameter! Must be a number between 1 and 31.\n\n";
        setColor(7);
        cin.clear();            
        cin.ignore(10000, '\n');
    }
    
  
    while (true) {
    	setColor(10);
        cout << "\tEnter Month (1-12): ";
        setColor(7);
        if (cin >> month && month >= 1 && month <= 12) {
            cin.ignore(10000, '\n'); // Clear extra text trailing the valid number
            break; // Month is correct! Break out of the month loop and move down
        }
        setColor(12);
        cout << "\tError: Invalid month parameter! Must be a number between 1 and 12.\n\n";
        cin.clear();            
        cin.ignore(10000, '\n');
    }
    
    
    while (true) {
    	setColor(10);
        cout << "\tEnter Year (1900-2026): ";
        setColor(7);
        if (cin >> year && year >= 1900 && year <= 2026) {
            cin.ignore(10000, '\n');
            break; // Year is correct! Break out entirely
        }
        setColor(12);
        cout << "\tError: Invalid year parameter! Must be between 1900 and 2026.\n\n";
        cin.clear();            
        cin.ignore(10000, '\n');
    }
    
    // 4. Combine into final string format
    char buffer[12]; 
    sprintf(buffer, "%02d/%02d/%04d", day, month, year);
    return string(buffer); 
}


class Contact {
protected:
    string name;
    string phone;
    string email;
    string citizenNo;

public:
    // 1. Default Constructor (Required to create arrays later)
    friend class PhoneBook;
    Contact() {
        name = "";
        phone = " ";
        email = "";
        citizenNo="";
    }

    // 2. Parameterized Constructor (To build contacts with data)
    Contact(string n, string p, string e, string c) {
        name = n;
        phone = p;
        email = e;
        citizenNo=c;
    }

    // 3. Simple Getter Functions to read private/protected variables safely
    string getName() const 
	{ 
		return name; 
	}
    string getPhone() const 
	{ 
		return phone; 
	}
    string getEmail() const 
	{ 
		return email; 
	}
	string getCitizenNo() const
	{
		return citizenNo;
	}
	
	bool operator==(const Contact& other) const {
        return phone == other.phone;
    }
	
	
	
    // You can also add your operator< here for the sorting feature
    bool operator<(const Contact& other) const {
        return toLowerCase(name) < toLowerCase(other.name);
    }

    // 4. Overloaded Operators (Required by your syllabus instructions)
    // Compares two contact names alphabetically for your sorting system
   virtual void save(ofstream& out) const
   {
   	out<<name<<endl<<phone<<endl<<email<<endl<<citizenNo<<endl;
   }
   virtual void load(ifstream& in) 
   {
   	getline(in,name);
   	getline(in,phone);
   	getline(in,email);
   	getline(in,citizenNo);
   }
   virtual void display() const
   {
   	setColor(10);cout<<"\tName: ";setColor(7);cout<<name;setColor(10);cout<<"\tPhone: ";setColor(7);cout<<phone;setColor(10);cout<<"\tEmail: ";setColor(7);cout<<email;setColor(10);cout<<"\tCitizen No: ";setColor(7);cout<<citizenNo;
   }
   virtual ~Contact()
   {
   }
};

class PersonalContact : public Contact {
	protected:
		string relation;
		string birthday;
		public:
			friend class PhoneBook;
			PersonalContact()
			{
				relation=" ";
				birthday=" ";
			}
			PersonalContact(string n, string p, string e, string c, string r, string bday):Contact( n, p, e,c)
			{
				relation=r;
				birthday=bday;
			}
			void save(ofstream& out) const override
			{
				Contact::save(out);
				out<<relation<<endl<<birthday<<endl;
			}
			void load(ifstream& in)  override
			{
				Contact::load(in);
				getline(in,relation);
				getline(in,birthday);
			}
			void display() const override { 
        	Contact::display(); 
        	setColor(10);cout << "\n\t| Type: Personal\t| Rel: ";setColor(7);cout << relation;setColor(10);cout << "\t| Bday: ";setColor(7);cout<< birthday << endl; }
	
};

class BusinessContact : public Contact {
	private:
	    string company;
	    string designation;
		public:
			friend class PhoneBook;
		    BusinessContact() 
			{
			company = ""; 
			designation = ""; 
			}
		    BusinessContact(string n, string p, string e, string c, string comp, string desig) : Contact(n, p, e,c)
			{
				company=comp;
				designation=desig;	
			} 
			
			 string getDesignation() const {
                return designation;
            }
            
		    void save(ofstream& out) const override 
			{
				Contact::save(out); 
				out << company << endl << designation << endl;
			}
		    void load(ifstream& in) override 
			{ 
				Contact::load(in); 
				getline(in, company); 
				getline(in, designation); 	
			}
		    
		    void display() const override 
			{ 
		        Contact::display(); 
		        setColor(10);cout << "\n\t| Type: Business\t| Co: ";setColor(7);cout << company;setColor(10);cout << "\t| Desig: ";setColor(7);cout << designation << endl; 
		    }
};

class PhoneBook 
{
	private:
	    PersonalContact personal[100];
	    BusinessContact business[100];
	    int pCount;
	    int bCount;
	    int i,j;

	public:
	    PhoneBook() 
		{ 
			pCount = 0; 
			bCount = 0; 
			i=0;
			j=0;
		}
	


	    void addContact() 
		{
	        int type=0;
	        while(true){
	        system("cls");
	        setColor(10);
	         cout << "\n\tSelect Contact Type:\n";
			cout << "\t| 1. Personal Contact\n";
			cout << "\t| 2. Business Contact\n";
			cout << "\t| 3. Exit            \n";
			cout << "\n\tEnter choice : ";
			setColor(7);
	        
	       if (cin >> type && type >= 1 && type <= 3) {
            cin.ignore(10000, '\n'); // Clear trailing characters out of the line buffer
            break; // Break the input loop when entry matches perfectly
        }
        
        setColor(12);
        cout << "\n\tInvalid choice! Please enter again. Press Enter to retry...";
        setColor(7);
        cin.clear();            // Reset the internal stream error state flags
        cin.ignore(10000, '\n'); // Purge corrupted variables out of the pipeline buffer
        cin.get(); 
}
			
			
			
	        if(type==3)
	        {
	        	return;
			}
			 if (type == 1 && pCount >= 100) {
			 	 setColor(12);
        cout << "\n\tError: Your Personal Contact space is completely full!" << endl;
         setColor(7);
        cin.get();
        return;
    }
    if (type == 2 && bCount >= 100) {
    	 setColor(12);
        cout << "\n\tError: Your Business Contact space is completely full!" << endl;
         setColor(7);
        cin.get();
        return;
    }
	        string n,c, e1, e2, e, p;
	        
	        system("cls");
	         
	        
	        
	        while (true) {
	        	 setColor(10);
                cout << "\tEnter Name: "; 
                 setColor(7);
                getline(cin, n);
                if (checkOnlyLetters(n) == true) {
                    break; // Name is valid, exit loop
                }
                 setColor(12);
                cout << "\tInvalid Input! Names can only contain alphabetical letters and spaces.\n" << endl;
                 
            }
	        
	        
	        while (true) {
	        	 setColor(10);
                cout << "\tEnter 10-Digit Phone: "; 
                 setColor(7);
                getline(cin, p);
                
                   bool containsLettersOrSymbols = false;
    for (int i = 0; i < p.length(); i++) {
        if (p[i] < '0' || p[i] > '9') {
            containsLettersOrSymbols = true;
            break;
        }
    }

    if (containsLettersOrSymbols) {
        setColor(12);
        cout << "\tError: No alphabets or symbols allowed!\n" << endl;
    } 
    else if (p.length() != 10) {
        setColor(12);
        cout << "\tError: Phone number must be exactly 10 digits!\n" << endl;
    } 
    else {
        break; 
    }
            }

			
	        try {
	            
	            Contact tempContact("", p, "","");
	            
	            for (int i = 0; i < pCount; i++) {
	                if (personal[i] == tempContact) { 
	                 setColor(12);
	                    throw DupException("Error: This phone number already exists in Personal Contacts!");
	                }
	                if (personal[i].getEmail()==e) { 
	                 setColor(12);
                    throw DupException("Error: This email already exists in Personal Contacts!");
                }
	            }
	            for (int i = 0; i < bCount; i++) {
	                if (business[i] == tempContact) {
	                 setColor(12);
	                    throw DupException("Error: This phone number already exists in Business Contacts!");
	                }
	                if (business[i].getEmail() == e) { 
	                 setColor(12);
                    throw DupException("Error: This email already exists in Personal Contacts!");
                }
	            }
	        
	            
	        
	           
			   while(true)
			   { 
			    setColor(10);
			cout<<"\tEnter email: ";
			 setColor(7);
			getline(cin,e);
			if(isValidEmail(e)==true)
			{
				break;
			}
			 setColor(12);
			cout<<"\tError please follow the proper format of email\n"<<endl;
		}
			
			
			for (int i = 0; i < pCount; i++) {
            if (personal[i].getEmail() == e) { 
                throw DupException("Error: This email already exists in Personal Contacts!");
            }
        }
        for (int i = 0; i < bCount; i++) {
            if (business[i].getEmail() == e) { 
                throw DupException("Error: This email already exists in Business Contacts!");
            }
        }
        
        
while (true) {
	 setColor(10);
            cout << "\tEnter Citizen Number (Digits & Hyphens only): ";
             setColor(7);
            getline(cin, c);
            if (isValidCitizenNo(c)) break;
             setColor(12);
            cout << "\tInvalid Citizen Number! Size must be 7-16 characters.\n\n";
        }


	for(int i=0;i<pCount;i++){
	if (personal[i].getCitizenNo() == c) {
	throw DupException("Error: Citizen ID already exists!");
}
}
for(int i=0;i<bCount;i++){
	if (business[i].getCitizenNo() == c) {
	throw DupException("Error: Citizen ID already exists!");
}
}


	            
	                       if (type == 1) 
            {
                
                while(true) {
                	 setColor(10);
                    cout << "\tEnter Relation: "; 
                     setColor(7);
                    getline(cin, e1);
                    if (checkOnlyLetters(e1) == true) {
                        break; 
                    }
                     setColor(12);
                    cout << "\tInvalid Input! Relation can only contain alphabetical letters and spaces.\n" << endl;
                }
                
                
                 setColor(10);
                    cout << "\tEnter Birthday (Numbers only, e.g., DD/MM/YYYY): "; 
                    e2 = askAndValidateBirthday(); 
                
                
                personal[pCount++] = PersonalContact(n, p,e, c, e1, e2);
            }
            else 
            {
                
                while(true) {
                	 setColor(10);
                    cout << "\tEnter Company Name: "; 
                     setColor(7);
                    getline(cin, e1);
                    if (checkOnlyLetters(e1) == true) { 
                        break;
                    }
                     setColor(12);
                    cout << "\tInvalid Input! Company Name can only contain letters and spaces.\n" << endl;
                }
                
                while(true) {
                	 setColor(10);
                    cout << "\tEnter Designation: "; 
                     setColor(7);
                    getline(cin, e2);
                    if (checkOnlyLetters(e2) == true) {
                        break;
                    }
                     setColor(12);
                    cout << "\tInvalid Input! Designation can only contain letters and spaces.\n" << endl;
                }
                
                business[bCount++] = BusinessContact(n, p,e, c, e1, e2);
            }

	            
	            // Sync to database file instantly
	            saveAll();
	             setColor(10);
	            cout << "\n\tContact cleanly added and saved to disk database!" << endl;
	    }
	        catch (DupException &e) {
	            cout << "\n\t" << e.getMessage() << endl;
	        }
	
	        cin.get();
	    }
	 
	

	    
	
	    void displayAll() const 
		{
	        system("cls");
	         setColor(10);
	        cout << "\t--- DIRECTORY RECORDS ---" << endl << endl;
	        for (int i = 0; i < pCount; i++) personal[i].display(); {}
			for (int i = 0; i < bCount; i++) business[i].display(); {}
	        cout << "\n\tPress Enter to return...";
	        cin.ignore(); 
			cin.get();
	    }
	
	   void saveAll() const 
		{
		    ofstream phoneOut("D://lang//phonebook.txt");
		    phoneOut << pCount << endl;
		    for (int i = 0; i < pCount; i++) 
			{
		        personal[i].save(phoneOut); 
		    }
		    
		    phoneOut << bCount << endl;
		    for (int i = 0; i < bCount; i++) 
			{
		        business[i].save(phoneOut);
		    }
		    
		    // Step F: Close the pipeline safely to lock the file down on your hard drive
		    phoneOut.close();
		}
	
	    void loadAll() {
	    ifstream in("D://lang//phonebook.txt");
		    if (!in) {
		        return;
		    }
		    
		    in >> pCount; 
		    in.ignore(); 
		    for (int i = 0; i < pCount; i++) {
		        personal[i].load(in); 
		    }
	    
		    in >> bCount;
		    in.ignore();
		    for (int i = 0; i < bCount; i++) {
		        business[i].load(in); //rebuilds
		    }
	    
	    in.close(); 
	}
		
		
		

void deleteContact() 
{
    int delChoice = 0;
    
    
    while (true) {
        system("cls");
         setColor(14);
        cout << "\t_________________________________________________\n\n";
        cout << "\t                 DELETE A CONTACT                \n";
        cout << "\t_________________________________________________\n\n";
         setColor(10);
        cout << "\tSelect deletion criteria:\n";
        cout << "\t| 1. Delete by Phone Number\n";
        cout << "\t| 2. Delete by Citizen Number\n";
        cout << "\t| 3. Exit back to Submenu\n";
        cout << "\n\tEnter your choice (1-3): ";
         setColor(7);
        
        if (cin >> delChoice && delChoice >= 1 && delChoice <= 3) {
            cin.ignore(10000, '\n'); // Clear trailing characters out of the line buffer
            break; // Break the input loop when entry matches perfectly
        }
        
        
         setColor(12);
        cout << "\n\tInvalid choice! Please enter again. Press Enter to retry...";
        setColor(7);
        cin.clear();            // Reset the internal stream error state flags
        cin.ignore(10000, '\n'); // Purge corrupted variables out of the pipeline buffer
        cin.get();              // Pause to let the user read the warning message
    }
    
    // Direct exit routing if the user picks option 3
    if (delChoice == 3) {
        return; 
    }
    cin.ignore();
    while(true){
    string targetKey = "";
    if (delChoice == 1) {
    	 setColor(10);
        cout << "\tEnter 10-Digit Phone Number to Delete: ";
         setColor(7);
        getline(cin, targetKey);
    } else {
    	 setColor(10);
        cout << "\tEnter Citizen Number to Delete: ";
         setColor(7);
        getline(cin, targetKey);
    }
    
    bool found = false;

    // Look inside Personal Contacts array structure
    for (int i = 0; i < pCount; i++) {
        bool match = (delChoice == 1) ? (personal[i].getPhone() == targetKey) : (personal[i].getCitizenNo() == targetKey);
        if (match) {
            found = true;
            for (int j = i; j < pCount - 1; j++) {
                personal[j] = personal[j + 1];
            }
            pCount--; 
            break;
        }
    }

    // If not found in personal, look inside Business Contacts array structure
    if (!found) {
        for (int i = 0; i < bCount; i++) {
            bool match = (delChoice == 1) ? (business[i].getPhone() == targetKey) : (business[i].getCitizenNo() == targetKey);
            if (match) {
                found = true;
                for (int j = i; j < bCount - 1; j++) {
                    business[j] = business[j + 1];
                }
                bCount--; 
                break;
            }
        }
    }

    if (found) {
    	
    	
    	
        
        saveAll(); // Sync clean working state directly back to text database file
         setColor(10);
        cout << "\n\tContact cleanly removed from database!" << endl;
        cout << "\n\tPress Enter to continue...";
            setColor(7);
            cin.get();
            return;
    } else {
    	 setColor(12);
        cout << "\n\tError: Contact records matching criteria not found." << endl;
        setColor(7);
    }
}
	 setColor(10);
    cout << "\n\tPress Enter to continue...";
    cin.get();
}



void searchByPhone() 
{
    system("cls");
    cin.ignore(); // Discard trailing newline characters safely
     setColor(14);
    string queryPhone;
    cout << "\t_________________________________________________\n\n";
    cout << "\t            SEARCH CONTACT BY PHONE              \n";
    cout << "\t_________________________________________________\n\n";
    setColor(10);
    cout << "\tEnter 10-Digit Phone Number to Search: ";
    setColor(7);
    getline(cin, queryPhone);

    bool found = false;

    // 1. Search within Personal Contacts array
    for (int i = 0; i < pCount; i++) {
        if (personal[i].getPhone() == queryPhone) {
        	setColor(10);
            cout << "\n\t--- MATCH FOUND IN PERSONAL CONTACTS ---\n\n";
            personal[i].display(); // Prints the detailed profile information
            found = true;
            break; // Stop looking since phone numbers are unique
        }
    }

    // 2. If not found in personal, search within Business Contacts array
    if (!found) {
        for (int i = 0; i < bCount; i++) {
            if (business[i].getPhone() == queryPhone) {
            	setColor(10);
                cout << "\n\t--- MATCH FOUND IN BUSINESS CONTACTS ---\n\n";
                business[i].display(); // Prints the detailed profile information
                found = true;
                break;
            }
        }
    }

    if (!found) {
    	setColor(12);
        cout << "\n\tError: No contact matching that phone number exists." << endl;
    }
setColor(10);
    cout << "\n\tPress Enter to return to search menu...";
    cin.get(); // Wait for user acknowledgment
}

void searchByName() 
{
    system("cls");
    cin.ignore(); // Discard trailing newline characters safely
    setColor(14);
    string queryName;
    cout << "\t_________________________________________________\n\n";
    cout << "\t            SEARCH CONTACT BY NAME               \n";
    cout << "\t_________________________________________________\n\n";
    setColor(10);
    cout << "\tEnter Name to Search: ";
    setColor(7);
    getline(cin, queryName);

    bool found = false;
	bool matchf = false;
	
    // 1. Search within Personal Contacts array
    for (int i = 0; i < pCount; i++) {
    	
        if (toLowerCase(personal[i].getName()) == toLowerCase(queryName)){
        	if(!matchf){
        		setColor(10);
           cout << "\n\t--- MATCH FOUND IN PERSONAL CONTACTS ---\n\n";
           matchf=true;}
           
            personal[i].display(); // Prints the detailed profile information
            found = true;
           
        }
    }

    // 2. If not found in personal, search within Business Contacts array
    if (!found) {
        for (int i = 0; i < bCount; i++) {
            if (toLowerCase(business[i].getName()) == toLowerCase(queryName)){
            	if(!matchf){
            		setColor(10);
                cout << "\n\t--- MATCH FOUND IN BUSINESS CONTACTS ---\n\n";
                matchf=true;}
                business[i].display(); // Prints the detailed profile information
                found = true;
               
            }
        }
    }

    if (!found) {
    	setColor(12);
        cout << "\n\tError: No contact matching that name exists." << endl;
    }
setColor(10);
    cout << "\n\tPress Enter to return to search menu...";
    cin.get(); // Wait for user acknowledgment
}

void searchByEmail() 
{
    system("cls");
    cin.ignore(); // Discard trailing newline characters safely
    setColor(14);
    string queryEmail;
    cout << "\t_________________________________________________\n\n";
    cout << "\t            SEARCH CONTACT BY EMAIL              \n";
    cout << "\t_________________________________________________\n\n";
    setColor(10);
    cout << "\tEnter Email to Search: ";
    setColor(7);
    getline(cin, queryEmail);

    bool found = false;

    // 1. Search within Personal Contacts array
    for (int i = 0; i < pCount; i++) {
        if (personal[i].getEmail() == queryEmail) {
        	setColor(10);
            cout << "\n\t--- MATCH FOUND IN PERSONAL CONTACTS ---\n\n";
            personal[i].display(); // Prints the detailed profile information
            found = true;
            break; // Stop looking since email are unique
        }
    }

    // 2. If not found in personal, search within Business Contacts array
    if (!found) {
        for (int i = 0; i < bCount; i++) {
            if (business[i].getEmail() == queryEmail) {
            	setColor(10);
                cout << "\n\t--- MATCH FOUND IN BUSINESS CONTACTS ---\n\n";
                business[i].display(); // Prints the detailed profile information
                found = true;
                break;
            }
        }
    }

    if (!found) {
    	setColor(12);
        cout << "\n\tError: No contact matching that email exists." << endl;
    }
setColor(10);
    cout << "\n\tPress Enter to return to search menu...";
    cin.get(); // Wait for user acknowledgment
}

void searchByCitizenNo() 
{
    system("cls");
    cin.ignore(); // Discard trailing newline characters safely
    setColor(12);
    string queryCitizen;
    cout << "\t_________________________________________________\n\n";
    cout << "\t        SEARCH CONTACT BY CITIZEN NO             \n";
    cout << "\t_________________________________________________\n\n";
    setColor(10);
    cout << "\tEnter Citizen No to Search: ";
    setColor(7);
    getline(cin, queryCitizen);

    bool found = false;

    // 1. Search within Personal Contacts array
    for (int i = 0; i < pCount; i++) {
        if (personal[i].getCitizenNo() == queryCitizen) {
        	setColor(10);
            cout << "\n\t--- MATCH FOUND IN PERSONAL CONTACTS ---\n\n";
            personal[i].display(); // Prints the detailed profile information
            found = true;
            break; // Stop looking since email are unique
        }
    }

    // 2. If not found in personal, search within Business Contacts array
    if (!found) {
        for (int i = 0; i < bCount; i++) {
            if (business[i].getCitizenNo() == queryCitizen) {
            	setColor(10);
                cout << "\n\t--- MATCH FOUND IN BUSINESS CONTACTS ---\n\n";
                business[i].display(); // Prints the detailed profile information
                found = true;
                break;
            }
        }
    }

    if (!found) {
    	setColor(12);
        cout << "\n\tError: No contact matching that citizen number exists." << endl;
    }
setColor(10);
    cout << "\n\tPress Enter to return to search menu...";
    cin.get(); // Wait for user acknowledgment
}


void searchByDesignation() 
{
    system("cls");
    cin.ignore(); // Discard trailing newline characters safely
    setColor(14);
    string queryDesig;
    cout << "\t_________________________________________________\n\n";
    cout << "\t          SEARCH BUSINESS BY DESIGNATION         \n";
    cout << "\t_________________________________________________\n\n";
    setColor(10);
    cout << "\tEnter Designation to Search: ";
    setColor(7);
    getline(cin, queryDesig);

    bool found = false;

    // Search strictly within Business Contacts array since Personal doesn't have designations
    for (int i = 0; i < bCount; i++) {
        if (toLowerCase(business[i].getDesignation()) == toLowerCase(queryDesig)) {
            if (!found) {
                setColor(10);
                cout << "\n\t--- MATCH(ES) FOUND IN BUSINESS CONTACTS ---\n\n";
            }
            business[i].display(); // Prints matching profile information
            found = true;
        }
    }

    if (!found) {
        setColor(12);
        cout << "\n\tError: No business contacts matching that designation exist." << endl;
    }
    setColor(10);
    cout << "\n\tPress Enter to return to search menu...";
    cin.get(); 
}



void sortAlphabetically() 
{
    system("cls");

    // 1. Sort Personal Contacts
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < pCount - 1; j++) {
            // Explicitly force a lowercase comparison right here to prevent ASCII casing bugs
            if (toLowerCase(personal[j].getName()) > toLowerCase(personal[j + 1].getName())) {
                PersonalContact temp = personal[j];
                personal[j] = personal[j + 1];
                personal[j + 1] = temp;
            }
        }
    }

    // 2. Sort Business Contacts
    for (int i = 0; i < bCount; i++) {
        for (int j = 0; j < bCount - 1; j++) {
            if (toLowerCase(business[j].getName()) > toLowerCase(business[j + 1].getName())) {
                BusinessContact temp = business[j];
                business[j] = business[j + 1];
                business[j + 1] = temp;
            }
        }
    }

    // 3. Save the newly sorted order permanently to the file
    saveAll();
setColor(14);
    // 4. Force a clean display right now to verify it worked!
    cout << "\t_________________________________________________\n\n";
    cout << "\t         ALPHABETICALLY SORTED DIRECTORY         \n";
    cout << "\t_________________________________________________\n\n";
    setColor(10);
    cout << "\n\t[ PERSONAL CONTACTS ]\n";
    for (int i = 0; i < pCount; i++) {
        personal[i].display();
    }
    
    cout << "\n\t[ BUSINESS CONTACTS ]\n";
    for (int i = 0; i < bCount; i++) {
        business[i].display();
    }

    cout << "\n\tDirectory sorted and saved to database successfully!" << endl;
    cout << "\tPress Enter to return...";
    
    cin.ignore();
    cin.get();
}

 void editContact() 
{
    
    
    int lookupMethod = 0;
    string targetPhone = "";
    while(true)
    {
	system("cls");
	setColor(14);
    cout << "\t_________________________________________________\n\n";
    cout << "\t                  EDIT A CONTACT                 \n";
    cout << "\t_________________________________________________\n\n";
    setColor(10);
    cout << "\tChoose how you want to find the contact:\n\n";
    cout << "\t| 1. Find directly by Phone Number\n";
    cout << "\t| 2. Find by Name (If you forgot the number)\n";
    cout << "\t| 3. Exit\n";
    cout << "\n\tEnter choice : ";
    setColor(7);
    
	
	if (cin >> lookupMethod && lookupMethod >= 1 && lookupMethod <= 3) {
            cin.ignore(10000, '\n'); 
            break; 
        }
        
        setColor(12);
        cout << "\n\tInvalid choice! Please enter again. Press Enter to retry...";
        cin.clear();            // Reset the system stream error pipeline flag status
        cin.ignore(10000, '\n'); // Clean garbage values out of structural stream buffers
        cin.get();              // Pause for visual notification confirmation text
    }
    
    
	if(lookupMethod==3)
	{
		return;
	}
    // METHOD 1: DIRECT BY PHONE NUMBER
    if (lookupMethod == 1) {
    	while(true){
        system("cls");
        setColor(10);
        cout << "\tEnter 10-Digit Phone Number of Target Contact: ";
        setColor(7);
        getline(cin, targetPhone);
        
        bool exists = false;
            for (int i = 0; i < pCount; i++) {
                if (personal[i].getPhone() == targetPhone) { exists = true; break; }
            }
            if (!exists) {
                for (int i = 0; i < bCount; i++) {
                    if (business[i].getPhone() == targetPhone) { exists = true; break; }
                }
            }
			if (exists) {
                break;
            }

            // If it doesn't exist, show error and loop back to ask again
            setColor(12);
            cout << "\n\tNo contact found with this phone number! Please try again.\n";
            cout << "\tPress Enter to retry...";
            setColor(7);
            cin.get();
    }
}

    // METHOD 2: LOOKUP BY NAME FIRST
    else if (lookupMethod == 2) {
        system("cls");
        string queryName;
        setColor(10);
        cout << "\tEnter Name to Search: ";
        setColor(7);
        getline(cin, queryName);

        

        bool matchFound = false;
        setColor(10);
        cout << "\n\t=================== MATCHING RECORDS ===================\n\n";

        for (int i = 0; i < pCount; i++) {
            if (toLowerCase(personal[i].getName()) == toLowerCase(queryName)) {
                personal[i].display();
                matchFound = true;
            }
        }

        for (int i = 0; i < bCount; i++) {
            if (toLowerCase(business[i].getName()) == toLowerCase(queryName)) {
                business[i].display();
                matchFound = true;
            }
        }

        if (!matchFound) {
        	setColor(12);
            cout << "\tNo contacts found matching the name: \"" << queryName << "\"\n";
            setColor(10);
            cout << "\n\tPress Enter to return to operations menu...";
            setColor(7);
            cin.get();
            return; 
        }
		setColor(10);
        cout << "\n\t========================================================\n\n";
        cout << "\tLook at the records above and copy the number exactly.\n";
        cout << "\tEnter the Phone Number of the contact to open editor: ";
        setColor(7);
        getline(cin, targetPhone);
        
        bool fo = false;
        for (int i = 0; i < pCount; i++) {
            if(personal[i].getPhone() == targetPhone) {
                system("cls");
                personal[i].display();
                fo = true;
            }
        }
        if(!fo) {
            for(int i = 0; i < bCount; i++) {
                if(business[i].getPhone() == targetPhone) {
                    system("cls");
                    business[i].display();
                    fo = true;
                }
            }
        }
    }
    else {
    	setColor(12);
        cout << "\n\tInvalid choice! Returning to menu..." << endl;   
		setColor(7);    
        cin.get();
        return;
    }
            
    // --- MAIN EDITOR LAYER ---
    bool found = false;
    int choice = 0;

    // LAUNCH EDITOR FOR PERSONAL ARRAY MATCH
    for (int i = 0; i < pCount; i++) {
        if (personal[i].getPhone() == targetPhone) {
            found = true;
            while (choice != 8) { 
                system("cls");
                setColor(14);
                cout << "\n\t--- EDIT PERSONAL CONTACT (" << personal[i].getName() << ") ---\n\n";
                setColor(10);
                cout << "\t| 1. Edit Name\n";
                cout << "\t| 2. Edit Phone Number  \n";
                cout << "\t| 3. Edit Email		   \n";
                cout << "\t| 4. Edit Relation	   \n";
                cout << "\t| 5. Edit Birthday	   \n";
                cout << "\t| 6. Edit Citizen Number\n";
                cout << "\t| 7. Update all   	   \n"; 
                cout << "\t| 8. Save & Back to Menu\n";
                cout << "\n\tEnter choice: ";
                setColor(7);
                cin >> choice;
                cin.ignore(); 

                                if (choice == 1) {
                    string oldName = personal[i].name; // Save original
                    while (true) {
                    	setColor(10);
                        cout << "\tEnter New Name: ";
                        setColor(7);
                        getline(cin, personal[i].name);
                        if (toLowerCase(personal[i].name) == toLowerCase(oldName)) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        if (checkOnlyLetters(personal[i].name)) {
                        	saveAll();
                        	setColor(10);
                            cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                            personal[i].display(); 
                            cout << "\n\tPress Enter to continue...";
                            cin.get();
                            break;
                        }
                        setColor(12);
                        cout << "\tInvalid! Letters and spaces only.\n\n";
                        setColor(7);
                    }
                }
                else if (choice == 2) {
                    string oldPhone = personal[i].phone; // Save original
                    while (true) {
                    	setColor(10);
                        cout << "\tEnter New 10-Digit Phone: ";
                        setColor(7);
                        getline(cin, personal[i].phone);
                        if (personal[i].phone == oldPhone) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        if (checkOnlyNumbers(personal[i].phone)) {
                        	saveAll();
                        	setColor(10);
                            cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                            personal[i].display(); 
                            cout << "\n\tPress Enter to continue...";
                            cin.get();
                            break;
                        }
                        setColor(12);
                        cout << "\tError: Must be exactly 10 digits!\n\n";
                        setColor(7);
                    }
                }
                                else if (choice == 3) {
                    string oldEmail = personal[i].email; 
                    while(true) {
                    	setColor(10);
                        cout << "\tEnter New Email: ";
                        setColor(7);
                        getline(cin, personal[i].email);
                        if (toLowerCase(personal[i].email) == toLowerCase(oldEmail)) {
                        	setColor(14);
                            cout << "\tPlease enter something new to update! It matches the old one.\n\n";
                            continue;
                        }
                        if (isValidEmail(personal[i].email)) {
                            break; // Valid layout structure, exit matching loop
                        }
                        setColor(12);
                        cout << "\tError: Invalid email structure format!\n\n";
                        setColor(7);
                    }
                    saveAll();
                    setColor(10);
                    cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                    personal[i].display(); 
                    cout << "\n\tPress Enter to continue...";
                    setColor(7);
                    cin.get();
                }

                else if (choice == 4) {
                    string oldRelation = personal[i].relation; // Save original
                    while (true) {
                    	setColor(10);
                        cout << "\tEnter New Relation: ";
                        setColor(7);
                        getline(cin, personal[i].relation);
                        if (toLowerCase(personal[i].relation) == toLowerCase(oldRelation)) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        if (checkOnlyLetters(personal[i].relation)) {
                        	saveAll();
                        	setColor(10);
                            cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                            personal[i].display(); 
                            cout << "\n\tPress Enter to continue...";
                            setColor(7);
                            cin.get();
                            break;
                        }
                        setColor(12);
                        cout << "\tInvalid! Letters and spaces only.\n\n";
                        setColor(7);
                    }
                }
                else if (choice == 5) {
                    string oldBirthday = personal[i].birthday; // Save original
                    while(true){
                    	setColor(10);
                        cout << "\tEnter New Birthday (dd/mm/yyyy): ";
                        setColor(7);
                        string tempBday = askAndValidateBirthday();
                        if (tempBday == oldBirthday) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        personal[i].birthday = tempBday;
                        saveAll();
                        setColor(10);
                        cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                        personal[i].display(); 
                        cout << "\n\tProfile updated successfully! Press any key to return to editor menu...";
                        cin.get();
                        break; // Fixed loop trap
                    }
                }

else if (choice == 6) { // NEW: Independent Citizen Update
                    string oldCit = personal[i].citizenNo;
                    while(true) {
                    	setColor(10);
                        cout << "\tEnter New Citizen Number: ";
                        setColor(7);
                        getline(cin, personal[i].citizenNo);
                        if (personal[i].citizenNo == oldCit) {
                        	setColor(14);
                            cout << "\tPlease enter something new to update! It matches the old one.\n\n";
                            setColor(7);
                            continue;
                        }
                        if (isValidCitizenNo(personal[i].citizenNo)) break;
                        setColor(12);
                        cout << "\tInvalid Citizen Number! Size must be 7-16 characters.\n\n";
                        setColor(7);
                    }
                    saveAll();
                    setColor(10);
                    cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                    personal[i].display(); 
                    cout << "\n\tPress Enter to continue...";
                    cin.get();
                }
                

                               else if (choice == 7) { 
                               system("cls");
                    setColor(14);
                    cout << "\n\tAre you sure you want to update all fields for this contact? (Y/N): ";
                    char confirm;
                    cin >> confirm;
                    cin.ignore(); // Clean formatting buffer space

                    if (confirm == 'n' || confirm == 'N') {
                        setColor(12);
                        cout << "\n\tUpdate cancelled! Returning to edit menu...\n";
                        setColor(10);
                        cout << "\tPress Enter to continue...";
                        cin.get();
                        continue; // Bypasses fields, loops right back to option list
                    }
                    system("cls");
                    setColor(10);
                    cout << "\n\t--- UPDATE ALL FIELDS (PERSONAL) ---\n\n";
                    
                    // 1. Name Sequential Update
                    string oldName = personal[i].name;
                    while (true) {
                        cout << "\tEnter New Name: ";
                        setColor(7);
                        getline(cin, personal[i].name);
                        if (toLowerCase(personal[i].name) == toLowerCase(oldName)) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        if (checkOnlyLetters(personal[i].name)) break;
                        setColor(12);
                        cout << "\tInvalid! Letters and spaces only.\n\n";
                        setColor(7);
                    }
                    
                    // 2. Phone Sequential Update
                    string oldPhone = personal[i].phone;
                    while (true) {
                    	setColor(10);
                        cout << "\tEnter New 10-Digit Phone: ";
                        setColor(7);
                        getline(cin, personal[i].phone);
                        if (personal[i].phone == oldPhone) {
                        	setColor(10);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        if (checkOnlyNumbers(personal[i].phone)) break;
                        setColor(12);
                        cout << "\tError: Must be exactly 10 digits!\n\n";
                        setColor(7);
                    }
                    
                    // 3. Email Sequential Update
                    string oldEmail = personal[i].email;
                    while (true) {
                    	setColor(10);
                        cout << "\tEnter New Email: ";
                        setColor(7);
                        getline(cin, personal[i].email);
                        if (toLowerCase(personal[i].email) == toLowerCase(oldEmail)) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        if(isValidEmail(personal[i].email))break;
                        setColor(14);
                        cout<<"\tError: Must be in email format (name@domain.com)\n\n";
                        setColor(7);
                        
                    }
                    
                    // 4. Relation Sequential Update
                    string oldRelation = personal[i].relation;
                    while (true) {
                    	setColor(10);
                        cout << "\tEnter New Relation: ";
                        setColor(7);
                        getline(cin, personal[i].relation);
                        if (toLowerCase(personal[i].relation) == toLowerCase(oldRelation)) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        if (checkOnlyLetters(personal[i].relation)) break;
                        setColor(12);
                        cout << "\tInvalid! Letters and spaces only.\n\n";
                        setColor(7);
                    }
                    
                    // 5. Birthday Sequential Update
                    string oldBirthday = personal[i].birthday;
                    while (true) {
                    	setColor(10);
                        cout << "\tEnter New Birthday (dd/mm/yyyy): ";
                        setColor(7);
                        string tempBday = askAndValidateBirthday();
                        if (tempBday == oldBirthday) {
                        	setColor(14);
                            cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                            setColor(7);
                            continue;
                        }
                        personal[i].birthday = tempBday;
                        break; 
                    }
                    
                    string oldCit = personal[i].citizenNo;
while(true) {
	setColor(10);
cout << "\tEnter New Citizen Number: ";
setColor(7);
getline(cin, personal[i].citizenNo);
if (personal[i].citizenNo == oldCit) {
	setColor(14);
cout << "\tPlease enter something new to update!\n\n"; 
setColor(17);
continue;
}
if (isValidCitizenNo(personal[i].citizenNo)) break;
setColor(12);
cout << "\tInvalid format! Size must be 7-16 characters.\n\n";
setColor(7);
}
                     
                    setColor(10);
                    cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                    personal[i].display(); 
                    saveAll();
					cout << "\n\tAll fields updated! Choose option 8 to save changes to disk.\n";
                    cin.get();}
                    else if (choice == 8) { // ? FIXED: Mapped option 8 directly to exit sequence
saveAll();
cout << "\n\tChanges saved successfully! Press Enter to return...";
cin.get();

}
                    
                
                

            }
            break;
        }
    }


    // LAUNCH EDITOR FOR BUSINESS ARRAY MATCH
    if (!found) {
        for (int i = 0; i < bCount; i++) {
            if (business[i].getPhone() == targetPhone) {
                found = true;
                while (choice != 8) { 
                
                    system("cls");
                    setColor(14);
                    cout << "\n\t--- EDIT BUSINESS CONTACT (" << business[i].getName() << ") ---\n\n";
                    setColor(10);
					cout << "\t| 1. Edit Name\n";
					cout << "\t| 2. Edit Phone Number\n";
					cout << "\t| 3. Edit Email\n";
					cout << "\t| 4. Edit Company Name\n";
					cout << "\t| 5. Edit Designation\n";
					cout << "\t| 6. Edit Citizen Number\n";
					cout << "\t| 7. UPDATE ALL FIELDS SEQUENTIALLY\n";
					cout << "\t| 8. Save & Back to Menu\n";
					cout << "\n\tEnter choice: ";
					setColor(7);
					cin >> choice;
					cin.ignore();
										if (choice == 1) {
                        string oldName = business[i].name; // Save original
						while (true) {
							setColor(10);
							cout << "\tEnter New Name: ";
							setColor(7);
							getline(cin, business[i].name);
                                if (toLowerCase(business[i].name) == toLowerCase(oldName)) {
                                	setColor(14);
                                    cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                    setColor(7);
                                    continue;
                                }
								if (checkOnlyLetters(business[i].name)) {
									saveAll();
									setColor(10);
								cout << "\n\t--- UPDATED PROFILE DATA ---\n";
								business[i].display(); 
								cout << "\n\tPress Enter to continue...";
								cin.get();
								break;
								}
								setColor(12);
							cout << "\tInvalid! Letters and spaces only.\n\n";
							setColor(7);
						}
					}
					else if (choice == 2) {
                        string oldPhone = business[i].phone; // Save original
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New 10-Digit Phone: ";
                            setColor(7);
                            getline(cin, business[i].phone);
                            if (business[i].phone == oldPhone) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (checkOnlyNumbers(business[i].phone)) {
                            	saveAll();
                            	setColor(10);
                                cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                                business[i].display(); 
                                cout << "\n\tPress Enter to continue...";
                                cin.get();
                                break;
                            }
                            setColor(12);
                            cout << "\tError: Must be exactly 10 digits!\n\n";
                            setColor(7);
                        }
					}
									else if (choice == 3) {
                        string oldEmail = business[i].email; 
                        while(true) {
                        	setColor(10);
                            cout << "\tEnter New Email: ";
                            setColor(7);
                            getline(cin, business[i].email);
                            if (toLowerCase(business[i].email) == toLowerCase(oldEmail)) {
                            	setColor(14);
                                cout << "\tPlease enter something new to update! It matches the old one.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (isValidEmail(business[i].email)) {
                                break;
                            }
                            setColor(12);
                            cout << "\tError: Invalid email structure format!\n\n";
                            setColor(7);
                        }
                        saveAll();
                        setColor(10);
                        cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                        business[i].display(); 
                        cout << "\n\tPress Enter to continue...";
                        cin.get();
					}

					else if (choice == 4) {
                        string oldCompany = business[i].company; // Save original
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New Company Name: ";
                            setColor(7);
                            getline(cin, business[i].company);
                            if (toLowerCase(business[i].company) == toLowerCase(oldCompany)) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (checkOnlyLetters(business[i].company)) {
                            	saveAll();
                            	setColor(10);
                                cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                                business[i].display(); 
                                cout << "\n\tPress Enter to continue...";
                                cin.get();
                                break;
                            }
                            setColor(12);
                            cout << "\tInvalid! Letters and spaces only.\n\n";
                            setColor(7);
                        }
					}
					else if (choice == 5) {
                        string oldDesignation = business[i].designation; // Save original
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New Designation: ";
                            setColor(7);
                            getline(cin, business[i].designation);
                            if (toLowerCase(business[i].designation) == toLowerCase(oldDesignation)) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (checkOnlyLetters(business[i].designation)) {
                            	saveAll();
                            	setColor(10);
                                cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                                business[i].display(); 
                                cout << "\n\tPress Enter to continue...";
                                cin.get();
                                break;
                            }
                            setColor(12);
                            cout << "\tInvalid! Letters and spaces only.\n\n";
                            setColor(7);
                        }
					}


else if (choice == 6) { // NEW: Independent Citizen Update
string oldCit = business[i].citizenNo;
while(true) {
	setColor(10);
cout << "\tEnter New Citizen Number: ";
setColor(7);
getline(cin, business[i].citizenNo);
if (business[i].citizenNo == oldCit) {
	setColor(14);
cout << "\tPlease enter something new to update! It matches the old one.\n\n";
setColor(7);
continue;
}
if (isValidCitizenNo(business[i].citizenNo)) break;
setColor(12);
cout << "\tInvalid Citizen Number! Size must be 7-16 characters.\n\n";
setColor(7);
}
saveAll();
setColor(10);
cout << "\n\t--- UPDATED PROFILE DATA ---\n";
business[i].display();
cout << "\n\tPress Enter to continue...";
cin.get();
}
										else if (choice == 7) {
											
											 system("cls");
                        setColor(14);
                        cout << "\n\tAre you sure you want to update all fields for this business contact? (Y/N): ";
                        char confirm;
                        cin >> confirm;
                        cin.ignore(); // Clean formatting buffer space

                        if (confirm == 'n' || confirm == 'N') {
                            setColor(12);
                            cout << "\n\tUpdate cancelled! Returning to edit menu...\n";
                            setColor(10);
                            cout << "\tPress Enter to continue...";
                            cin.get();
                            continue; // Bypasses inputs completely
                        }
                        
                        
                        system("cls");
                        setColor(14);
                        cout << "\n\t--- UPDATE ALL FIELDS (BUSINESS) ---\n\n";
                        
                        // 1. Name Sequential Update
                        string oldName = business[i].name;
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New Name: ";
                            setColor(7);
                            getline(cin, business[i].name);
                            if (toLowerCase(business[i].name) == toLowerCase(oldName)) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (checkOnlyLetters(business[i].name)) break;
                            setColor(12);
                            cout << "\tInvalid! Letters and spaces only.\n\n";
                            setColor(7);
                        }
                        
                        // 2. Phone Sequential Update
                        string oldPhone = business[i].phone;
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New 10-Digit Phone: ";
                            setColor(7);
                            getline(cin, business[i].phone);
                            if (business[i].phone == oldPhone) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (checkOnlyNumbers(business[i].phone)) break;
                            setColor(12);
                            cout << "\tError: Must be exactly 10 digits!\n\n";
                            setColor(7);
                        }
                        
                        // 3. Email Sequential Update
                        string oldEmail = business[i].email;
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New Email: ";
                            setColor(7);
                            getline(cin, business[i].email);
                            if (toLowerCase(business[i].email) == toLowerCase(oldEmail)) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if(isValidEmail(business[i].email))break;
                            setColor(12);
                            cout<<"\tError: Must be in the format of email (name@domain.com)\n\n";
                            setColor(7);
                            
                        }
                        
                        // 4. Company Name Sequential Update
                        string oldCompany = business[i].company;
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New Company Name: ";
                            setColor(7);
                            getline(cin, business[i].company);
                            if (toLowerCase(business[i].company) == toLowerCase(oldCompany)) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (checkOnlyLetters(business[i].company)) break;
                            setColor(12);
                            cout << "\tInvalid! Letters and spaces only.\n\n";
                            setColor(7);
                        }
                        
                        // 5. Designation Sequential Update
                        string oldDesignation = business[i].designation;
                        while (true) {
                        	setColor(10);
                            cout << "\tEnter New Designation: ";
                            setColor(7);
                            getline(cin, business[i].designation);
                            if (toLowerCase(business[i].designation) == toLowerCase(oldDesignation)) {
                            	setColor(14);
                                cout << "\tPlease enter smth new to update! It matches the old thing.\n\n";
                                setColor(7);
                                continue;
                            }
                            if (checkOnlyLetters(business[i].designation)) break;
                            setColor(12);
                            cout << "\tInvalid! Letters and spaces only.\n\n";
                            setColor(7);
                        }
                        
                        string oldCit = business[i].citizenNo;
while(true) {
	setColor(10);
cout << "\tEnter New Citizen Number: ";
setColor(7);
getline(cin, business[i].citizenNo);
if (business[i].citizenNo == oldCit) {
	setColor(14);
cout << "\tPlease enter something new to update!\n\n";
setColor(7); 
continue;
}
if (isValidCitizenNo(business[i].citizenNo)) break;
setColor(12);
cout << "\tInvalid format! Size must be 5-20 characters.\n\n";
setColor(7);
}}
                        else if(choice==8)
                        {
                        	setColor(10);
                        cout << "\n\t--- UPDATED PROFILE DATA ---\n";
                        business[i].display(); 
                        saveAll();
                        cout << "\n\tAll fields updated! Choose option 7 to save changes to disk.\n";
                        cin.get();
					}
				}
				break;
			}
		}
	}
}};







class Page {
private:

    string userid;
    string password;
    string ruserid;
    string rpassword;
    string suserid;

public:
    
    void login();
    void registration();
    
    void menu(); 
    string getHiddenPassword();
    friend class Dash;
};

class Dash
{
	public:
		friend class Page;
		friend class PhoneBook;
		void me();
};

void Dash::me()
{
	PhoneBook pb;
	pb.loadAll();
	int b;
	while (b != 4) 
	{
	system("cls");
	setColor(14);
    cout<<"\t\t\t_________________________________________________\n\n\n"; 
    cout<<"\t\t\t 	  PHONE BOOK MANAGEMENT SYSTEM          \n\n\n"; 
    cout<<"\t\t\t_________________________________________________\n\n\n"; 
    cout<<"\n"; 
    cout<<"\n"; 
    setColor(10);
    cout<<"\t| 1. Contact Operation       "<<endl; 
    cout<<"\t| 2. Search Contact 	      "<<endl;    //search by name
    cout<<"\t| 3. Contact Sorting         "<<endl;    //sort alphabetically
    cout<<"\t| 4. Exit					  "<<endl;
    cout<<"\n\t Enter your choice: "; 
    setColor(7);
    cin>>b; 
    cout<<endl; 
    
    switch(b)
    {
    	case 1:
    		{
    		int c=0;
    		while(c!=5){
			
    		system("cls");
    		setColor(10);
    		cout<<"\t| 1. Add Contact	          	  "<<endl; 
		    cout<<"\t| 2. Display All Contacts 	      "<<endl; 
		    cout<<"\t| 3. Edit Contact				  "<<endl;
		    cout<<"\t| 4. Delete Contact			  "<<endl;
		    cout<<"\t| 5. Menu           			  "<<endl;
		    cout<<"\n\t Enter your choice: ";
			setColor(7); 
		    cin>>c; 

			if (c == 1) {
                    pb.addContact();
                    
                }
                else if (c == 2) {
                    pb.displayAll();
                }
                else if (c == 3) {
                    pb.editContact();
                }
                else if (c == 4) {
                    pb.deleteContact();
                }
           
	          } // me(); 
	            break;
        }
        case 2:
		{
            int d=0;
            while(d!=6)
			{
            system("cls");
            setColor(10);
            cout<<"\t| 1. Search Contact by PhoneNumber "<<endl; 
		    cout<<"\t| 2. Search Contact by Name        "<<endl;
			cout<<"\t| 3. Search Contact by Email	    "<<endl; 
			cout<<"\t| 4. Search Contact by Citizen No  "<<endl;
			cout<<"\t| 5. Search Business by Designation"<< endl;
		    cout<<"\t| 6. Menu                          "<<endl;  
		    cout<<"\n\t Enter your choice: ";
		    setColor(7);
		    cin>>d;
		    
		    if(d==1)
		    {
		    	pb.searchByPhone();
			}
			else if(d==2)
			{
				pb.searchByName();
			}
			else if(d==3)
			{
				pb.searchByEmail();
			}
			else if(d==4)
			{
				pb.searchByCitizenNo();
			}
			else if (d == 5) 
			{ 
				pb.searchByDesignation(); 
			}
        }
        //me();
        break;
		}
        case 3:
        	pb.sortAlphabetically();
        	system("cls");
        	me();
            break;
        case 4:
        {
        	system("cls");
            Page obj;
            obj.menu();
            break;
        }
          default: 
		   {
                setColor(12); // Red text color
                cout << "\tInvalid Option! Please enter a number between 1 and 4.\n";
                cout << "\tPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
    }
    }
}


void Page::menu() 
{
    int a;
    setColor(14);
    cout<<"\t\t\t_________________________________________________\n\n\n"; 
    cout<<"\t\t\t             WElCOME TO THE LOGIN PAGE           \n\n\n"; 
    cout<<"\t\t\t________________________ MENU ___________________\n\n\n"; 
    cout<<"\n"; 
    cout<<"\n"; 
    setColor(10);
    cout<<"\t| press 1 to LOGIN           |"<<endl; 
    cout<<"\t| press 2 to REGISTER        |"<<endl; 
    cout<<"\t| press 3 to EXIT            |"<<endl; 
    cout<<"\n\t Enter your choice: "; 
    setColor(7);
    cin>>a; 
    cout<<endl; 
    
    switch(a) 
    { 
        case 1: 
            login(); 
            break; 
        case 2: 
            registration(); 
            break;  
        case 3: 
           	system("cls");
			exit(0);
			break;

        default: 
            system("cls"); 
            setColor(14);
            cout<<"\t\t\t Please select from the options given above \n"<<endl; 
            setColor(7);
            cin.ignore();
            cin.get();
            system("cls");
            menu(); 
    } 
}

string Page::getHiddenPassword() {
    string hiddenPass = "";
    char singleKey;
    
    // Read keys one by one until user hits Enter (\r)
    while ((singleKey = _getch()) != '\r') {
        
        // CHECK IF THE USER PRESSED BACKSPACE
        if (singleKey == '\b') {
            // Only delete if there is actually a character to remove
            if (hiddenPass.length() > 0) {
                // 1. Remove the last character from your password string
                hiddenPass.erase(hiddenPass.length() - 1);
                
                // 2. Erase the last '*' from the console screen visually
                cout << "\b \b";
            }
        } 
        else {
            // If it's a regular key, add it and print a star normally
            hiddenPass += singleKey; 
            cout << "*";             
        }
    }
    cout << endl;
    return hiddenPass;
}


void Page::login() 
{ 
    int count = 0; 
    string id, pass; 
    system("cls"); 
    setColor(14);
    cout<<"\t\t\t Enter the username and password :"<<endl; 
    setColor(10);
    cout<<"\t\t\t USERNAME: ";
	setColor(7); 
    cin>>userid; 
    setColor(10);
    cout<<"\t\t\t PASSWORD: "; 
    setColor(7);
    password=getHiddenPassword(); 
    
    ifstream input("D://lang//records.txt"); 
    while(input>>id>>pass) 
    { 
        if(id==userid && pass==password) 
        { 
            count=1; 
            system("cls"); 
        } 
    } 
    input.close(); 
    
    if(count==1) 
    { 
        system("cls"); 
        setColor(10);
        cout<<userid<<" your LOGIN is successful \n "; 
        cin.ignore(); 
        cin.get(); 
        system("cls"); 
        Dash ob;
		ob.me(); 
    } 
    else{ 
        system("cls"); 
        setColor(12);
        cout<<"\n login error \n Please check your username and password\n"; 
        setColor(7);
        cin.ignore(); 
        cin.get(); 
        system("cls"); 
        menu(); 
    } 
} 

void Page::registration() 
{ 
    system("cls"); 
    setColor(10);
    cout<<"\t\t\t Enter the username: ";
	setColor(7); 
    cin>>ruserid; 
    setColor(10);
    cout<<"\t\t\t Enter the password: "; 
    setColor(7);
    rpassword=getHiddenPassword();
    
    ofstream fool("D://lang//records.txt",ios::app); 
    fool<<ruserid<<"\t"<<rpassword<<endl; 
    
    system("cls"); 
    setColor(10);
    cout<<"\n\t\t\t Registration is successful! \n"; 
    cin.ignore(); 
    cin.get(); 
    system("cls"); 
    menu(); 
} 


int main() 
{
    Page p; 
    p.menu(); 
    
    return 0;
}













