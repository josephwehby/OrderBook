#include "wx/wx.h"
#include "OrderBook.hpp"
#include <memory>

class Main : public wxFrame{
public:
    Main();
	~Main();
    void onButtonClick(OrderType);
    wxDECLARE_EVENT_TABLE();


private:
    void clearOrderBook();
    void onBuyClick(wxCommandEvent &evt);
    void onAskClick(wxCommandEvent &evt);
    OrderBook orderbook;    
    wxStaticText* price_text = nullptr;
    wxStaticText* quantity_text = nullptr;
    wxStaticText* bid = nullptr;
	wxStaticText* ask = nullptr;

    wxButton* buy = nullptr;
    wxButton* sell = nullptr;
    
    wxTextCtrl* price = nullptr;
    wxTextCtrl* quantity = nullptr;

    wxListBox* bidbox = nullptr;
    wxListBox* askbox = nullptr;
};