#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class studentNode {
public:
    int s_id = 0;
    string s_name = "";
    float gpa = 0.0;
    string s_pass = "";
    studentNode* s_pnext = NULL;
};

class courseNode {
public:
    int c_id = 0;
    string c_name = "";
    int maxseats = 0;
    int c_enrollment = 0;
    courseNode* c_pnext = NULL;
};

class enrollmentNode {
public:
    int e_id = 0;
    string grade = "";
    int s_id = 0;
    int c_id = 0;
    enrollmentNode* e_pnext = NULL;
};

class adminNode {
public:
    int a_id = 0;
    string a_name = "";
    string a_pass = "";
    adminNode* a_pnext = NULL;
};

class studentlist {
public:
    studentNode* s_ph;
    studentNode* s_pt;

    studentlist() {
        s_ph = NULL;
        s_pt = NULL;
    }

    void attach(studentNode* pnn) {
        if (s_ph == NULL) {
            s_ph = pnn;
            s_pt = pnn;
        }
        else {
            s_pt->s_pnext = pnn;
            s_pt = pnn;
        }
    }

    void loadfromfile()
    {
        ifstream students("students.txt");
        string s;
        int t;

        if (students.is_open())
        {
            while (getline(students, s))
            {
                string temp[4];
                t = 0;
                for (int i = 0; i < s.length(); i++)
                {
                    if (s[i] == ',')
                    {
                        t++;
                    }
                    else
                    {
                        temp[t] += s[i];
                    }
                }
                studentNode* pnn = new studentNode;
                pnn->s_id = stoi(temp[0]);
                pnn->s_name = temp[1];
                pnn->gpa = stof(temp[2]);
                pnn->s_pass = temp[3];
                pnn->s_pnext = NULL;

                attach(pnn);
            }
            students.close();
        }

    }

    void savefromfile()
    {
        ofstream students("students.txt");


        studentNode* ptrav = s_ph;
        while (ptrav != NULL)
        {
            students << ptrav->s_id << ","
                << ptrav->s_name << ","
                << ptrav->gpa << ","
                << ptrav->s_pass << endl;
            ptrav = ptrav->s_pnext;
        }
        students.close();

    }

    void registerstudent()
    {
        int id;
        string name, pass;

        cout << "Enter your password : ";
        cin >> pass;
        cout << "Enter your name : ";
        cin >> name;
        cout << "Enter your ID : ";
        cin >> id;

        studentNode* pnn = new studentNode;
        pnn->s_id = id;
        pnn->s_name = name;
        pnn->gpa = 0.0;
        pnn->s_pass = pass;
        pnn->s_pnext = NULL;

        attach(pnn);
        savefromfile();
        cout << "Student registered successfully!" << endl;
    }

    int login()
    {
        int id;
        string pass;

        cout << "Enter your ID: ";
        cin >> id;

        cout << "Enter Password: ";
        cin >> pass;

        studentNode* trav = s_ph;
        while (trav != NULL)
        {
            if (trav->s_id == id && trav->s_pass == pass)
            {
                cout << "Welcome, " << trav->s_name << "!" << endl;
                return 1;
            }
            trav = trav->s_pnext;
        }

        cout << "Invalid credentials!" << endl;
        return 0;
    }

    studentNode* searchbyid(int id)
    {
        studentNode* ptrav = s_ph;
        while (ptrav != NULL)
        {
            if (ptrav->s_id == id)
            {
                return ptrav;
            }
            ptrav = ptrav->s_pnext;
        }
        return NULL;
    }

    void createStudent()
    {
        int id;
        string name, pass;
        float gpa;

        cout << "Enter Student ID: ";
        cin >> id;

        if (searchbyid(id) != NULL)
        {
            cout << "Error: Student ID already exists!" << endl;
            return;
        }

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter GPA: ";
        cin >> gpa;

        cout << "Enter Password: ";
        cin >> pass;

        studentNode* pnn = new studentNode;
        pnn->s_id = id;
        pnn->s_name = name;
        pnn->gpa = gpa;
        pnn->s_pass = pass;
        pnn->s_pnext = NULL;

        attach(pnn);
        savefromfile();

        cout << "Student created successfully!" << endl;
    }

    void updatestudent() {
        int id;
        cout << "Enter student ID you want to update : ";
        cin >> id;

        studentNode* student = searchbyid(id);

        if (student == NULL)
        {
            cout << "Student not found!" << endl;
            return;
        }

        cout << "Current Name: " << student->s_name << endl;
        cout << "Enter new name: ";

        string newname;
        cin >> newname;
        if (!newname.empty())
        {
            student->s_name = newname;
        }

        cout << "Enter new password: ";
        string newpass;
        cin >> newpass;
        if (!newpass.empty())
        {
            student->s_pass = newpass;
        }

        savefromfile();
        cout << "Student updated successfully!" << endl;
    }

    void updategpa() {
        int id;
        cout << "id : ";
        cin >> id;
        float newgpa;
        cout << "enter new gpa : ";
        cin >> newgpa;

        studentNode* curr = s_ph;
        while (curr != NULL)
        {
            if (curr->s_id == id)
            {
                curr->gpa = newgpa;
                savefromfile();
                cout << "GPA updated" << endl;
                return;
            }
            curr = curr->s_pnext;
        }
        cout << "ID not found" << endl;
    }

    void deletestudent()
    {
        int id;
        cout << "student id you want to delete : ";
        cin >> id;

        studentNode* curr = s_ph;
        studentNode* prev = NULL;

        while (curr != NULL)
        {
            if (curr->s_id == id)
            {
                if (prev == NULL)
                {
                    s_ph = curr->s_pnext;
                }
                else
                {
                    prev->s_pnext = curr->s_pnext;
                }
                if (curr == s_pt)
                {
                    s_pt = prev;
                }
                delete curr;
                savefromfile();
                cout << "Student with ID " << id << " deleted from list." << endl;
                return;
            }
            prev = curr;
            curr = curr->s_pnext;
        }

        cout << "Student with ID " << id << " not found in the list." << endl;
    }

    void displaybyid() {
        int id;
        cout << "student id you want : ";
        cin >> id;

        studentNode* student = searchbyid(id);
        if (student != NULL)
        {
            cout << " Student Details " << endl;
            cout << "ID: " << student->s_id << endl;
            cout << "Name: " << student->s_name << endl;
            cout << "GPA: " << student->gpa << endl;
        }
        else
        {
            cout << "Student not found!" << endl;
        }
    }

    void displayall()
    {
        if (s_ph == NULL)
        {
            cout << "No students in the system." << endl;
            return;
        }

        int ct = 0;
        studentNode* trav = s_ph;
        while (trav != NULL)
        {
            ct++;
            cout << "student " << ct << " : ";
            cout << "id:" << trav->s_id << ", ";
            cout << "name:" << trav->s_name << ", ";
            cout << "gpa:" << trav->gpa << endl;
            trav = trav->s_pnext;
        }
    }

    ~studentlist() {
        studentNode* trav = s_ph;
        while (s_ph != NULL) {
            s_ph = trav->s_pnext;
            delete trav;
            trav = s_ph;
        }
        s_pt = NULL;
    }
};

class courselist {
public:
    courseNode* c_ph;
    courseNode* c_pt;

    courselist() {
        c_ph = NULL;
        c_pt = NULL;
    }

    void attach(courseNode* pnn)
    {
        if (c_ph == NULL)
        {
            c_ph = pnn;
            c_pt = pnn;
        }
        else
        {
            c_pt->c_pnext = pnn;
            c_pt = pnn;
        }
    }

    void loadfromfile()
    {
        ifstream courses("courses.txt");
        string c;
        int t;

        if (courses.is_open())
        {
            while (getline(courses, c))
            {

                string temp[4];
                t = 0;
                for (int i = 0; i < c.length(); i++)
                {
                    if (c[i] == ',')
                    {
                        t++;
                    }
                    else {
                        temp[t] += c[i];
                    }
                }
                courseNode* pnn = new courseNode;
                pnn->c_id = stoi(temp[0]);
                pnn->c_name = temp[1];
                pnn->maxseats = stoi(temp[2]);
                pnn->c_enrollment = stoi(temp[3]);
                pnn->c_pnext = NULL;

                attach(pnn);
            }
            courses.close();
        }

    }

    void savefromfile()
    {
        ofstream courses("courses.txt");


        courseNode* ptrav = c_ph;
        while (ptrav != NULL)
        {
            courses << ptrav->c_id << ","
                << ptrav->c_name << ","
                << ptrav->maxseats << ","
                << ptrav->c_enrollment << endl;
            ptrav = ptrav->c_pnext;
        }
        courses.close();

    }

    courseNode* searchbyid(int cid)
    {
        courseNode* trav = c_ph;
        while (trav != NULL)
        {
            if (trav->c_id == cid)
            {
                return trav;
            }
            trav = trav->c_pnext;
        }
        return NULL;
    }

    void createcourse()
    {
        int id, maxseats;
        string name;

        cout << "Enter Course ID: ";
        cin >> id;

        if (searchbyid(id) != NULL)
        {
            cout << "Error: Course ID already exists!" << endl;
            return;
        }

        cout << "Enter Course Name: ";
        cin >> name;

        cout << "Enter Max Seats: ";
        cin >> maxseats;

        courseNode* pnn = new courseNode;
        pnn->c_id = id;
        pnn->c_name = name;
        pnn->maxseats = maxseats;
        pnn->c_enrollment = 0;
        pnn->c_pnext = NULL;

        attach(pnn);
        savefromfile();
        cout << "Course created successfully!" << endl;
    }

    void updatecourse()
    {
        int id;
        cout << "Enter course ID to update: ";
        cin >> id;

        courseNode* course = searchbyid(id);

        if (course == NULL)
        {
            cout << "Course not found!" << endl;
            return;
        }

        cout << "Current name: " << course->c_name << endl;
        cout << "Enter new name: ";
        string newname;
        cin >> newname;

        if (newname.length() != 0)
        {
            course->c_name = newname;
        }

        cout << "Current Max Seats: " << course->maxseats << endl;
        cout << "Enter new max seats: ";
        int newMax;
        cin >> newMax;

        if (newMax != -1)
        {
            if (newMax < course->c_enrollment)
            {
                cout << "Error: Cannot set max seats less than current enrollment!" << endl;
            }
            else
            {
                course->maxseats = newMax;
            }
        }

        savefromfile();
        cout << "Course updated successfully!" << endl;
    }

    void deletecoursebyid()
    {
        int id;
        cout << "course id you want to delete : ";
        cin >> id;

        courseNode* curr = c_ph;
        courseNode* prev = NULL;

        while (curr != NULL)
        {
            if (curr->c_id == id)
            {
                if (prev == NULL)
                {
                    c_ph = curr->c_pnext;
                }
                else
                {
                    prev->c_pnext = curr->c_pnext;
                }
                if (curr == c_pt) {
                    c_pt = prev;
                }
                delete curr;
                savefromfile();
                cout << "course with ID " << id << " deleted from list." << endl;
                return;
            }
            prev = curr;
            curr = curr->c_pnext;
        }

        cout << "course with ID " << id << " not found in the list." << endl;
    }

    void dispallcourses()
    {
        courseNode* ptrav = c_ph;
        if (ptrav == NULL)
        {
            cout << "No courses available :( " << endl;
            return;
        }
        cout << "These are all the available courses: " << endl;
        while (ptrav != NULL)
        {
            cout << "course id: " << ptrav->c_id << endl;
            cout << "course name: " << ptrav->c_name << endl;
            cout << "max seats number: " << ptrav->maxseats << endl;
            cout << "course current enrollment: " << ptrav->c_enrollment << endl;
            cout << "course available seats: " << ptrav->maxseats - ptrav->c_enrollment << endl;

            ptrav = ptrav->c_pnext;
        }
    }

    void enrollmentstatistics()
    {
        if (c_ph == NULL)
        {
            cout << "No courses in the system." << endl;
            return;
        }

        int flag = 0;
        courseNode* trav = c_ph;

        while (trav != NULL) {
            int available = trav->maxseats - trav->c_enrollment;

            if (available <= 5) {
                flag = 1;
                cout << trav->c_id << " "
                    << trav->c_name << " "
                    << available;
                if (available == 0) {
                    cout << " (CLOSED)";
                }
                cout << endl;
            }

            trav = trav->c_pnext;
        }

        if (flag == 0)
        {
            cout << "All courses have more than 5 available seats." << endl;
        }
    }

    ~courselist() {
        courseNode* trav = c_ph;
        while (c_ph != NULL)
        {
            c_ph = trav->c_pnext;
            delete trav;
            trav = c_ph;
        }
        c_pt = NULL;
    }
};

class enrollmentlist
{
public:
    enrollmentNode* e_ph;
    enrollmentNode* e_pt;

    enrollmentlist()
    {
        e_ph = NULL;
        e_pt = NULL;
    }

    void attach(enrollmentNode* pnn)
    {
        if (e_ph == NULL)
        {
            e_ph = pnn;
            e_pt = pnn;
        }
        else
        {
            e_pt->e_pnext = pnn;
            e_pt = pnn;
        }
    }

    void loadfromfile()

    {
        ifstream enrollments("enrollments.txt");
        string x;

        if (enrollments.is_open())
        {
            while (getline(enrollments, x))
            {

                string temp[4];
                int t = 0;

                for (int i = 0; i < x.length(); i++)
                {
                    if (x[i] == ',')
                    {
                        t++;
                    }
                    else
                    {
                        temp[t] += x[i];
                    }
                }

                enrollmentNode* pnn = new enrollmentNode;
                pnn->e_id = stoi(temp[0]);
                pnn->s_id = stoi(temp[1]);
                pnn->c_id = stoi(temp[2]);
                pnn->grade = temp[3];
                pnn->e_pnext = NULL;

                attach(pnn);
            }
            enrollments.close();
        }

    }

    void savefromfile()
    {
        ofstream enrollments("enrollments.txt");


        enrollmentNode* ptrav = e_ph;
        while (ptrav != NULL)
        {
            enrollments << ptrav->e_id << ","
                << ptrav->s_id << ","
                << ptrav->c_id << ","
                << ptrav->grade << endl;
            ptrav = ptrav->e_pnext;
        }
        enrollments.close();

    }

    int getNextEnrolmentId()
    {
        if (e_ph == NULL)
        {
            return 1;
        }

        int maxid = 0;
        enrollmentNode* trav = e_ph;
        while (trav != NULL)
        {
            if (trav->e_id > maxid)
            {
                maxid = trav->e_id;
            }
            trav = trav->e_pnext;
        }
        return maxid + 1;
    }

    void enrollstudent(int studentId, int courseId, courselist& cl)
    {
        courseNode* course = cl.searchbyid(courseId);

        if (course == NULL)
        {
            cout << "Error: Course not found!" << endl;
            return;
        }

        if (course->c_enrollment >= course->maxseats)
        {
            cout << "Error: Course is full!" << endl;
            return;
        }

        enrollmentNode* trav = e_ph;
        while (trav != NULL)
        {
            if (trav->s_id == studentId && trav->c_id == courseId)
            {
                cout << "Error: Already enrolled in this course!" << endl;
                return;
            }
            trav = trav->e_pnext;
        }

        enrollmentNode* pnn = new enrollmentNode;
        pnn->e_id = getNextEnrolmentId();
        pnn->s_id = studentId;
        pnn->c_id = courseId;
        pnn->grade = "";
        pnn->e_pnext = NULL;

        attach(pnn);
        course->c_enrollment++;
        cl.savefromfile();
        savefromfile();

        cout << "Successfully enrolled in course ID " << courseId << "!" << endl;
    }

    void viewtranscript(courselist& cl)
    {
        int found = 0;
        int id;
        cout << "student ID for transcript: ";
        cin >> id;

        enrollmentNode* trav = e_ph;
        while (trav != NULL)
        {
            if (trav->s_id == id)
            {
                found = 1;

                courseNode* course = cl.searchbyid(trav->c_id);

                cout << trav->c_id << " : ";

                if (course != NULL)
                {
                    cout << course->c_name << " , ";
                }
                else
                {
                    cout << "Unknown course ";
                }
                if (trav->grade.length() == 0)
                {
                    cout << "in prograss";
                }
                else
                {
                    cout << trav->grade;
                }


                cout << endl;
            }
            trav = trav->e_pnext;
        }

        if (found == 0)
        {
            cout << "No enrollments found." << endl;
        }
    }

    void coursereport(int cid, studentlist& sl, courselist& cl)
    {
        courseNode* c = cl.searchbyid(cid);
        if (c == NULL)
        {
            cout << "Course not found." << endl;
            return;
        }

        cout << "Course report for: " << c->c_name
            << " (ID " << c->c_id << ")" << endl;

        int flag = 0;
        enrollmentNode* trav = e_ph;
        while (trav != NULL)
        {
            if (trav->c_id == cid)
            {
                flag = 1;

                studentNode* s = sl.searchbyid(trav->s_id);
                string name;

                if (s != NULL)
                {
                    name = s->s_name;
                }
                else
                {
                    name = "Unknown";
                }


                cout << "Student ID: " << trav->s_id
                    << ", Name: " << name
                    << ", Grade: " << trav->grade
                    << endl;
            }
            trav = trav->e_pnext;
        }

        if (flag == 0)
        {
            cout << "No students enrolled in this course." << endl;
        }
    }

    void updategrade()
    {
        int id;
        cout << "enter enrolment id to update grade: ";
        cin >> id;
        string newGrade;
        cout << "enter new grade: ";
        cin >> newGrade;

        enrollmentNode* trav = e_ph;
        while (trav != NULL)
        {
            if (trav->e_id == id)
            {
                trav->grade = newGrade;
                savefromfile();
                cout << "Grade updated successfully!" << endl;
                return;
            }
            trav = trav->e_pnext;
        }
        cout << "Enrollment not found!" << endl;
    }

    void displayall()
    {
        if (e_ph == NULL)
        {
            cout << "No enrollments in the system." << endl;
            return;
        }

        enrollmentNode* trav = e_ph;
        while (trav != NULL)
        {
            cout << trav->e_id << " "
                << trav->s_id << " "
                << trav->c_id << " ";
            if (trav->grade.empty())
            {
                cout << "Not Graded";
            }
            else {
                cout << trav->grade;
            }
            cout << endl;

            trav = trav->e_pnext;
        }
    }

    ~enrollmentlist() {
        enrollmentNode* trav = e_ph;
        while (e_ph != NULL) {
            e_ph = trav->e_pnext;
            delete trav;
            trav = e_ph;
        }
        e_pt = NULL;
    }
};

class adminlist {
public:
    adminNode* a_ph;
    adminNode* a_pt;

    adminlist()
    {
        a_ph = NULL;
        a_pt = NULL;
    }

    void attach(adminNode* pnn)
    {
        if (a_ph == NULL)
        {
            a_ph = pnn;
            a_pt = pnn;
        }
        else
        {
            a_pt->a_pnext = pnn;
            a_pt = pnn;
        }
    }

    void loadfromfile()
    {
        ifstream admin("admin.txt");
        string x;

        if (admin.is_open())
        {
            while (getline(admin, x))
            {

                string temp[3];
                int t = 0;

                for (int i = 0; i < x.length(); i++)
                {
                    if (x[i] == ',')
                    {
                        t++;
                    }
                    else
                    {
                        temp[t] += x[i];
                    }
                }

                adminNode* pnn = new adminNode;
                pnn->a_id = stoi(temp[0]);
                pnn->a_name = temp[1];
                pnn->a_pass = temp[2];
                pnn->a_pnext = NULL;

                attach(pnn);
            }
            admin.close();
        }

    }

    void savefromfile()
    {
        ofstream admin("admin.txt");


        adminNode* ptrav = a_ph;
        while (ptrav != NULL) {
            admin << ptrav->a_id << ","
                << ptrav->a_name << ","
                << ptrav->a_pass << endl;

            ptrav = ptrav->a_pnext;
        }
        admin.close();

    }

    int login()
    {
        int id;
        string pass;

        cout << "Enter Admin ID: ";
        cin >> id;

        cout << "Enter Password: ";
        cin >> pass;

        adminNode* trav = a_ph;
        while (trav != NULL)
        {
            if (trav->a_id == id && trav->a_pass == pass) {
                cout << "Welcome Admin, " << trav->a_name << "!" << endl;

                return 1;
            }
            trav = trav->a_pnext;
        }

        cout << "Invalid admin credentials!" << endl;
        return 0;
    }

    void displayall()
    {
        if (a_ph == NULL)
        {
            cout << "No admins in the system." << endl;
            return;
        }

        adminNode* trav = a_ph;
        while (trav != NULL)
        {
            cout << trav->a_id << "\t" << trav->a_name << endl;
            trav = trav->a_pnext;
        }
    }

    ~adminlist() {
        adminNode* trav = a_ph;
        while (a_ph != NULL) {
            a_ph = trav->a_pnext;
            delete trav;
            trav = a_ph;
        }
        a_pt = NULL;
    }
};

int main()
{
    int n;
    int flag = 0;
    int sid, cid;

    studentlist sl;
    courselist cl;
    enrollmentlist el;
    adminlist al;

    sl.loadfromfile();
    cl.loadfromfile();
    el.loadfromfile();
    al.loadfromfile();

    cout << "Welcome to your course management system! " << endl;

    while (flag == 0)
    {
        cout << endl
            << "1- Student login" << endl
            << "2- Admin login" << endl
            << "3- Register (Student)" << endl
            << "4- Close system" << endl
            << "Choose : ";
        cin >> n;

        if (n == 1)
        {
            if (sl.login())
            {
                int i;
                int k = 0;
                while (k == 0)
                {
                    cout << "1- Browse courses" << endl
                        << "2- Enrol in course" << endl
                        << "3- View transcript" << endl
                        << "4- Logout";
                    cout << endl;
                    cout << "Choose: ";
                    cin >> i;

                    if (i == 1)
                    {
                        cl.dispallcourses();
                    }
                    if (i == 2)
                    {
                        cout << "Please enter your id: ";
                        cin >> sid;
                        cout << "Please enter course id to enroll: ";
                        cin >> cid;

                        el.enrollstudent(sid, cid, cl);
                    }
                    if (i == 3)
                    {
                        el.viewtranscript(cl);
                    }
                    if (i == 4)
                    {
                        k = 1;

                    }
                }
            }
        }
        if (n == 2)
        {
            if (al.login())
            {
                int i;
                int k = 0;
                while (k == 0)
                {
                    cout << "1- Create student" << endl
                        << "2- Update student" << endl
                        << "3- delete student" << endl
                        << "4- Update student GPA" << endl
                        << "5- create course" << endl
                        << "6- Update course" << endl
                        << "7- Delete course" << endl
                        << "8- Course report" << endl
                        << "9- Enrollment statistics" << endl
                        << "10- Logout" << endl
                        << "Choose: ";
                    cin >> i;

                    if (i == 1)
                    {
                        sl.createStudent();
                    }
                    if (i == 2)
                    {
                        sl.updatestudent();
                    }
                    if (i == 3)
                    {
                        sl.deletestudent();
                    }
                    if (i == 4)
                    {
                        sl.updategpa();
                    }
                    if (i == 5)
                    {
                        cl.createcourse();
                    }
                    if (i == 6)
                    {
                        cl.updatecourse();
                    }
                    if (i == 7)
                    {
                        cl.deletecoursebyid();
                    }
                    if (i == 8)
                    {
                        cout << "Enter course ID ";
                        cin >> cid;

                        el.coursereport(cid, sl, cl);
                    }
                    if (i == 9)
                    {
                        cl.enrollmentstatistics();
                    }
                    if (i == 10)
                    {
                        k = 1;
                    }
                }
            }
        }
        if (n == 3)
        {
            sl.registerstudent();
        }
        if (n == 4)
        {
            flag = 1;
            cout << endl << "sytsem end ";
        }

    }

    return 0;
}
