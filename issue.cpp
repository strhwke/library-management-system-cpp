#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <windows.h>

using namespace std;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

void issue_db(string bid, string bStudentID) {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "archis2004", "library", 0, NULL, 0);
    if (conn) {
        cout << bid << "--" << bStudentID << "--issue\n";

        stringstream ss;
        ss << "SELECT * FROM books WHERE available='YES' AND bid='" << bid << "';";
        string checkavailability = ss.str();
        cout << checkavailability << endl;

        if (mysql_query(conn, checkavailability.c_str())) {
            cout << mysql_error(conn) << endl;
            return;
        }
        res = mysql_use_result(conn);
        int flag = 0;
        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << endl;
            if (strcmp(row[0], bid.c_str()) == 0) {
                flag = 1;
                break;
            }
        }

        ss.str("");
        ss << "SELECT * FROM student WHERE sid='" << bStudentID << "';";
        string checkstudent = ss.str();
        cout << checkstudent << endl;

        if (mysql_query(conn, checkstudent.c_str())) {
            cout << mysql_error(conn) << endl;
            return;
        }
        res = mysql_use_result(conn);
        int tag = 0;
        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << endl;
            if (strcmp(row[0], bStudentID.c_str()) == 0) {
                tag = 1;
                break;
            }
        }

        if (flag == 1 && tag == 1) {
            ss.str("");
            ss << "UPDATE books SET available='NO' WHERE bid='" << bid << "';";
            string updatequery = ss.str();
            cout << updatequery << endl;

            if (mysql_query(conn, updatequery.c_str())) {
                cout << mysql_error(conn) << endl;
                return;
            }

            ss.str("");
            ss << "INSERT INTO issue VALUES('" << bid << "','" << bStudentID << "');";
            string addquery = ss.str();
            cout << addquery << endl;

            if (mysql_query(conn, addquery.c_str())) {
                cout << mysql_error(conn) << endl;
                return;
            }

            MessageBox(NULL, "Book issued successfully", "Success", MB_ICONINFORMATION | MB_OK);
        }
        else {
            if (flag == 0) {
                MessageBox(NULL, "Book not available", "Error", MB_ICONERROR | MB_OK);
            }
            else {
                MessageBox(NULL, "Invalid student", "Error", MB_ICONERROR | MB_OK);
            }
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
    else {
        cout << "Connection failed" << endl;
    }
}

void issueBooks() {
    string bid, bStudentID;

    cout << "issue" << endl;

    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, 0, 650, 200, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    cout << "       Issue Books\n\n";

    cout << "Enter Book id: ";
    cin >> bid;
    cout << "Enter Student ID: ";
    cin >> bStudentID;

    issue
