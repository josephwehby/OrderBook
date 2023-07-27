#include "wx/wx.h"
#include "OrderBook.hpp"
#include <memory>
#include <sstream>

class Main : public wxFrame{
public:
    Main();
	~Main();
    // void onButtonClick(OrderType);
private:
    void resetOrderBook();
    
    OrderBook orderbook;    
    wxStaticText* mid_price = nullptr;
	wxStaticText* spread = nullptr;
    wxStaticText* bid = nullptr;
	wxStaticText* ask = nullptr;
    wxListBox* bidbox = nullptr;
    wxListBox* askbox = nullptr;
};