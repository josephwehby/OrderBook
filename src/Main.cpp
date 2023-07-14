#include "Main.hpp"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
    EVT_BUTTON(10002, Main::onButtonClick)
    EVT_BUTTON(10003, Main::onButtonClick)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Limit Order Book", wxPoint(30, 30), wxSize(700, 350)) {
	
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

    price_text = new wxStaticText(this, wxID_ANY, "Price", wxPoint(10, 10), wxSize(50,30));
    price = new wxTextCtrl(this, 10000, "", wxPoint(80, 10), wxSize(130, 30));

    quantity_text = new wxStaticText(this, wxID_ANY, "Qty", wxPoint(10, 50), wxSize(50,30));
    quantity = new wxTextCtrl(this, 10001, "", wxPoint(80, 50), wxSize(130, 30));
    
    buy = new wxButton(this, 10002, "Buy", wxPoint(10, 100), wxSize(95,40));
    buy->SetBackgroundColour(wxColour(*wxGREEN));
    buy->SetFont(font);

    sell = new wxButton(this, 10003, "Sell", wxPoint(115, 100), wxSize(95,40));
    sell->SetBackgroundColour(wxColour(*wxRED));
    sell->SetFont(font);

    bidbox = new wxListBox(this, 10004, wxPoint(300, 10), wxSize(150, 200));
    askbox = new wxListBox(this, 10005, wxPoint(450, 10), wxSize(150, 200));
}

Main::~Main() {

}

void Main::onButtonClick(wxCommandEvent &evt) {
    
    std::string order_price = (price->GetValue()).ToStdString();
    std::string order_quantity = (quantity->GetValue()).ToStdString();

    std::string order = order_price + " " + order_quantity;

    bidbox->Append(wxString(order));
    evt.Skip();
}