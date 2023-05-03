#include <iostream>
#include <string>
#include <mysqlx/xdevapi.h>
#include <mysqlx/devapi/mysqlx_error.h>
#include <mysqlx/devapi/mysqlx_exception.h>
#include <gtkmm.h>

using namespace std;
using namespace mysqlx;

class AddBooksWindow : public Gtk::Window
{
public:
    AddBooksWindow();
    virtual ~AddBooksWindow();

protected:
    // Signal handlers:
    void on_submit_button_clicked();

    // Child widgets:
    Gtk::Label m_greeting_label;
    Gtk::Label m_id_label;
    Gtk::Entry m_id_entry;
    Gtk::Label m_title_label;
    Gtk::Entry m_title_entry;
    Gtk::Label m_author_label;
    Gtk::Entry m_author_entry;
    Gtk::Button m_submit_button;
};

AddBooksWindow::AddBooksWindow()
    : m_greeting_label("Add Books"), m_id_label("Enter Book id: "), m_title_label("Enter Title: "),
      m_author_label("Enter Author: "), m_submit_button("Submit")
{
    set_title("SRM Central Library Management System");
    set_border_width(10);

    // Add widgets to the window
    Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    add(*vbox);

    m_greeting_label.set_halign(Gtk::ALIGN_CENTER);
    m_greeting_label.set_valign(Gtk::ALIGN_CENTER);
    m_greeting_label.set_size_request(-1, 50);
    m_greeting_label.override_font(Pango::FontDescription("Arial Bold 30"));
    vbox->add(m_greeting_label);

    Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());
    grid->set_row_spacing(10);
    grid->set_column_spacing(10);
    vbox->add(*grid);

    grid->attach(m_id_label, 0, 0, 1, 1);
    grid->attach(m_id_entry, 1, 0, 1, 1);
    grid->attach(m_title_label, 0, 1, 1, 1);
    grid->attach(m_title_entry, 1, 1, 1, 1);
    grid->attach(m_author_label, 0, 2, 1, 1);
    grid->attach(m_author_entry, 1, 2, 1, 1);
    grid->attach(m_submit_button, 0, 3, 2, 1);

    m_submit_button.signal_clicked().connect(sigc::mem_fun(*this, &AddBooksWindow::on_submit_button_clicked));

    show_all_children();
}

AddBooksWindow::~AddBooksWindow()
{
}

void AddBooksWindow::on_submit_button_clicked()
{
    std::string id_str = m_id_entry.get_text();
    std::string title_str = m_title_entry.get_text();
    std::string author_str = m_author_entry.get_text();

    // Connect to the database
    Session session(SessionOption::HOST, "localhost", SessionOption::PORT, 33060, SessionOption::USER, "root",
                    SessionOption::PWD, "archis2004", SessionOption::DB, "library");
    Schema db = session.getSchema("library");
    Table books_tbl = db.getTable("books");

    // Insert the book record
    Row row = books_tbl.newRow();
    row["id"] = id_str;
    row["title"] = title_str;
    row["author"] = author_str;
    row["available"] = true;
    try
    {
        books_tbl.insert(row).execute();
        Gtk::MessageDialog dlg(*
