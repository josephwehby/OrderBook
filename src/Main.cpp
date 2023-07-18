#include "Main.hpp"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
    EVT_BUTTON(10002, Main::onBuyClick)
    EVT_BUTTON(10003, Main::onAskClick)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Limit Order Book", wxPoint(30, 30), wxSize(700, 455)) {
	
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

    mid_price = new wxStaticText(this, wxID_ANY, "0.00", wxPoint(430, 10), wxSize(50,30));
    spread = new wxStaticText(this, wxID_ANY, "0.00", wxPoint(430, 40), wxSize(50,30));
    mid_price->SetFont(font);
    spread->SetFont(font);
    bid = new wxStaticText(this, wxID_ANY, "Bid", wxPoint(360, 80), wxSize(50,30));
    bid->SetFont(font);
    bidbox = new wxListBox(this, 10004, wxPoint(300, 100), wxSize(150, 200));
    bidbox->SetForegroundColour(wxColour(*wxGREEN));
    
    ask = new wxStaticText(this, wxID_ANY, "Ask", wxPoint(510, 80), wxSize(50,30));
    ask->SetFont(font);
    askbox = new wxListBox(this, 10005, wxPoint(450, 100), wxSize(150, 200));
    askbox->SetForegroundColour(wxColour(*wxRED));
}

Main::~Main() {

}

void Main::onBuyClick(wxCommandEvent &evt) {
    onButtonClick(Buy);
    evt.Skip();
}

void Main::onAskClick(wxCommandEvent &evt) {
    onButtonClick(Sell);
    evt.Skip();
}

void Main::resetOrderBook() {
    std::stringstream ss;
    std::string str_spread, str_mid;
    askbox->Clear();  
    bidbox->Clear();
    orderbook.wxOrderDisplay(Buy, bidbox);
    orderbook.wxOrderDisplay(Sell, askbox);
    
    ss.precision(3);
    ss << std::fixed << orderbook.getSpread();
    ss >> str_spread;
    ss.clear();
    ss << std::fixed << orderbook.getMidPrice();
    ss >> str_mid;

    spread->SetLabel(wxString(str_spread));
    mid_price->SetLabel(wxString(str_mid));
}

void Main::onButtonClick(OrderType order_type) {
    std::shared_ptr<Order> order;
    double share_price;
    unsigned int qty;
    
    std::string order_price = (price->GetValue()).ToStdString();
    std::string order_quantity = (quantity->GetValue()).ToStdString();
    
    sscanf(order_price.c_str(), "%lf", &share_price);
    sscanf(order_quantity.c_str(), "%d", &qty);

    // add order 
    if (order_price != "" && order_quantity != "") {
        order = std::make_shared<Order>(order_type, qty, share_price);
        orderbook.addOrder(order);
    }
    
    resetOrderBook();
}