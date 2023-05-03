#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include "add.hpp"
#include "delete.hpp"
#include "issue.hpp"
#include "Return.hpp"
#include "view.hpp"
#include "add_student.hpp"
#include "delete_student.hpp"
#include "view_student.hpp"
#include "view_issued.hpp"

MYSQL* db;

int main() {
    db = mysql_init(NULL);
    if (db == NULL) {
        std::cerr << "Error: mysql_init() failed\n";
        exit(1);
    }
    db = mysql_real_connect(db, "localhost", "root", "archis2004", "library", 0, NULL, 0);
    if (db == NULL) {
        std::cerr << "Error: mysql_real_connect() failed\n";
        exit(1);
    }
    std::cout << "Successfully connected to the database\n";

    // Create the window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SRM Central Library Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 650, 500);

    // Create the welcome label
    GtkWidget* greet = gtk_label_new("Welcome to SRM Central Library");
    PangoFontDescription* font = pango_font_description_from_string("Times New Roman 30");
    gtk_widget_modify_font(greet, font);
    gtk_label_set_justify(GTK_LABEL(greet), GTK_JUSTIFY_CENTER);
    // Create the buttons
    GtkWidget* addbtn = gtk_button_new_with_label("Add Books");
    GtkWidget* deletebtn = gtk_button_new_with_label("Delete Books");
    GtkWidget* issuebtn = gtk_button_new_with_label("Issue Books");
    GtkWidget* returnbtn = gtk_button_new_with_label("Return Books");
    GtkWidget* viewbtn = gtk_button_new_with_label("View Books");
    GtkWidget* addstudbtn = gtk_button_new_with_label("Add Students");
    GtkWidget* delstudbtn = gtk_button_new_with_label("Delete Students");
    GtkWidget* viewstudbtn = gtk_button_new_with_label("View Students");
    GtkWidget* viewissuedbtn = gtk_button_new_with_label("View Issued Books");

    // Set the button font and size
    font = pango_font_description_from_string("Arial 20");
    gtk_widget_modify_font(addbtn, font);
    gtk_widget_modify_font(deletebtn, font);
    gtk_widget_modify_font(issuebtn, font);
    gtk_widget_modify_font(returnbtn, font);
    gtk_widget_modify_font(viewbtn, font);
    gtk_widget_modify_font(addstudbtn, font);
    gtk_widget_modify_font(delstudbtn, font);
    gtk_widget_modify_font(viewstudbtn, font);
    gtk_widget_modify_font(viewissuedbtn, font);

    // Add the buttons to the window
    gtk_grid_attach(GTK_GRID(grid), addbtn, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), deletebtn, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), issuebtn, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), returnbtn, 0, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), viewbtn, 0, 10, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addstudbtn, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), delstudbtn, 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), viewstudbtn, 2, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), viewissuedbtn, 2, 8, 1, 1);

    // Connect signals to the buttons
    g_signal_connect(G_OBJECT(addbtn), "clicked", G_CALLBACK(addBooks), NULL);
    g_signal_connect(G_OBJECT(deletebtn), "clicked", G_CALLBACK(deleteBooks), NULL);
    g_signal_connect(G_OBJECT(issuebtn), "clicked", G_CALLBACK(issueBooks), NULL);
    g_signal_connect(G_OBJECT(returnbtn), "clicked", G_CALLBACK(returnBooks), NULL);
    g_signal_connect(G_OBJECT(viewbtn), "clicked", G_CALLBACK(viewBooks), NULL);
    g_signal_connect(G_OBJECT(addstudbtn), "clicked", G_CALLBACK(addStudents), NULL);
    g_signal_connect(G_OBJECT(delstudbtn), "clicked", G_CALLBACK(deleteStudents), NULL);
    g_signal_connect(G_OBJECT(viewstudbtn), "clicked", G_CALLBACK(viewStudents), NULL);
    g_signal_connect(G_OBJECT(viewissuedbtn), "clicked", G_CALLBACK(viewIssuedBooks), NULL);

    // Create the developer label
    GtkWidget* greet4 = gtk_label_new("developed by : ARCHISMAN HES");
    gtk_label_set_justify(GTK_LABEL(greet4), GTK_JUSTIFY_CENTER);
    gtk_grid_attach(GTK_GRID(grid), greet4, 0, 19, 3, 1);

    // Show all widgets
    gtk_widget_show
