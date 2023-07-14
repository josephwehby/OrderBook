#include "wx/wx.h"

class Main : public wxFrame{
public:
    Main();
	~Main();
    void onButtonClick(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();


private:
    wxStaticText* price_text = nullptr;
    wxStaticText* quantity_text = nullptr;
	wxButton* buy = nullptr;
    wxButton* sell = nullptr;
    wxTextCtrl* price = nullptr;
    wxTextCtrl* quantity = nullptr;

    wxListBox* bidbox = nullptr;
    wxListBox* askbox = nullptr;
};