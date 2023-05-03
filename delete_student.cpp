#include <iostream>
#include <string>
#include <mysqlx/xdevapi.h>
#include <gtk/gtk.h>

using namespace std;
using namespace mysqlx;

GtkWidget* id;

void delete_students() {

    string sid;
    sid = gtk_entry_get_text(GTK_ENTRY(id));

    // Connect to the database
    Session sess("localhost", 33060, "root", "archis2004");
    Schema db = sess.getSchema("library");

    cout << sid << "--delete" << endl;

    try {
        string sqlquery = "select * from student where sid='" + sid + "';";
        cout << sqlquery << endl;
        RowResult res = db.getDefaultCollection().execute(sqlquery).execute();
        bool flag = false;
        Row row;
        while ((row = res.fetchOne())) {
            if (row[0] == sid) {
                flag = true;
                cout << flag << endl;
                cout << sid << endl;
                break;
            }
        }
        if (flag) {
            string delquery1 = "delete from student where sid='" + sid + "';";
            cout << delquery1 << endl;
            db.getDefaultCollection().execute(delquery1).execute();
            GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Student removed Successfully");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        else {
            GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Student not found");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
    catch (const mysqlx::Error& e) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Student with given id does not exist");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    gtk_widget_destroy(GTK_WIDGET(gtk_widget_get_parent(id)));
}

void deleteStudents() {

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SRM Central Library Management System");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* greet = gtk_label_new("Delete Student");
    gtk_label_set_markup(GTK_LABEL(greet), "<span font_desc='30' foreground='red'>Delete Student</span>");
    gtk_grid_attach(GTK_GRID(gtk_bin_get_child(GTK_BIN(window))), greet, 0, 0, 3, 1);

    GtkWidget* L = gtk_label_new("Enter Student id: ");
    gtk_grid_attach(GTK_GRID(gtk_bin_get_child(GTK_BIN(window))), L, 0, 2, 1, 1);

    id = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(id), 5);
    gtk_grid_attach(GTK_GRID(gtk_bin_get_child(GTK_BIN(window))), id, 2, 2, 1, 1);

    GtkWidget* submitbtn = gtk_button_new_with_label("Submit");
    g_signal_connect(submitbtn, "clicked", G_CALLBACK(delete_students), NULL);
    gtk_widget_set_hexpand(submitbtn, TRUE);
    gtk_widget_set_margin_start(submitbtn, 90);
    gtk_widget_set_margin_end(submitbtn, 90);
    gtk_grid_attach(GTK_GRID(gtk_bin_get_child(GTK_BIN(window))), submitbtn, 0, 4, 3, 1);

    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char* argv[]) {

    gtk_init(&argc, &argv);
    deleteStudents();
    return 0;
}

