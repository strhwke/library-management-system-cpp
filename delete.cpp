#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;

void delete_db() {
    string bid = id.get();
    string query = "SELECT * FROM books WHERE bid='" + bid + "'";
    int flag = 0;

    if (mysql_query(conn, query.c_str())) {
        cerr << "Error: " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        if (row[0] == bid) {
            flag = 1;
            break;
        }
    }

    mysql_free_result(res);

    if (flag == 0) {
        cout << "Book not found" << endl;
        return;
    }

    query = "DELETE FROM books WHERE bid='" + bid + "'";

    if (mysql_query(conn, query.c_str())) {
        cerr << "Error: " << mysql_error(conn) << endl;
        return;
    }

    cout << "Book removed successfully" << endl;
}

void deleteBooks() {
    cout << "Delete Books" << endl;
    string winTitle = "SRM Central Library Management System";
    string greet = "Delete Books";
    string enterId = "Enter Book ID: ";
    string submitBtn = "Submit";

    // Create window
    GtkWidget* window;
    GtkWidget* label;
    GtkWidget* entry;
    GtkWidget* button;

    gtk_init(0, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), winTitle.c_str());
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

    // Create label
    label = gtk_label_new(greet.c_str());
    gtk_label_set_markup(GTK_LABEL(label), "<span font='30' weight='bold'>" + greet + "</span>");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 3, 1);

    // Create ID label and entry
    label = gtk_label_new(enterId.c_str());
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);

    entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 5);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 1, 1);

    // Create submit button
    button = gtk_button_new_with_label(submitBtn.c_str());
    g_signal_connect(button, "clicked", G_CALLBACK(delete_db), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 3, 1);

    gtk_widget_show_all(window);

    gtk_main();
}

int main(int argc, char** argv) {
    string host = "localhost";
    string user = "root";
    string password = "archis2004";
    string database = "library";
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0)) {
        cerr << "Error: " << mysql_error(conn) << endl;
        exit(1);
    }

    deleteBooks();

    mysql_close(conn);

    return 0;
}
