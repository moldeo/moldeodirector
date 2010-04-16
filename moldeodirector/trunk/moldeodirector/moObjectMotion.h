#ifndef MOOBJECTMOTION_H
#define MOOBJECTMOTION_H

#include "moDirectorTypes.h"
#include "moIDirectorActions.h"

//(*Headers(moObjectMotion)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/statbmp.h>
//*)

class moObjectMotion: public wxPanel, public moIDirectorActions
{
	public:

		moObjectMotion(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~moObjectMotion();
		void Inspect( moValueDescriptor  p_ValueDescriptor );

		//(*Declarations(moObjectMotion)
		wxTextCtrl* TextCtrlTx;
		wxSlider* SliderSx;
		wxPanel* PanelScalesTxt;
		wxBitmapButton* BitmapButtonScaVer;
		wxTextCtrl* TextCtrlSy;
		wxStaticBitmap* StaticBitmap5;
		wxPanel* PanelPosition;
		wxBitmapButton* BitmapButtonRotHor;
		wxPanel* Panel4;
		wxTextCtrl* TextCtrlSz;
		wxStaticBitmap* StaticBitmap1;
		wxTextCtrl* TextCtrlTy;
		wxTextCtrl* TextCtrlRx;
		wxSlider* SliderTz;
		wxBitmapButton* BitmapButtonPosVer;
		wxPanel* Panel1;
		wxBitmapButton* BitmapButton8;
		wxBitmapButton* BitmapButtonPosCircular;
		wxPanel* Panel6;
		wxPanel* Panel3;
		wxBitmapButton* BitmapButtonScaDiag;
		wxTextCtrl* TextCtrlRy;
		wxBitmapButton* BitmapButtonRotRand;
		wxTextCtrl* TextCtrlRz;
		wxTextCtrl* TextCtrlSx;
		wxBitmapButton* BitmapButtonRotCircular;
		wxPanel* Panel7;
		wxBitmapButton* BitmapButtonScaHor;
		wxSlider* SliderRx;
		wxBitmapButton* BitmapButtonScaCircular;
		wxBitmapButton* BitmapButtonPosHor;
		wxBitmapButton* BitmapButtonRotDiag;
		wxSlider* SliderTy;
		wxSlider* SliderRy;
		wxBitmapButton* BitmapButtonScaRand;
		wxTextCtrl* TextCtrlTz;
		wxPanel* Panel2;
		wxPanel* PanelTranslateCoords;
		wxBitmapButton* BitmapButtonRotVer;
		wxSlider* SliderRz;
		wxSlider* SliderTx;
		wxPanel* PanelScales;
		wxStaticBitmap* StaticBitmap3;
		wxSlider* SliderSz;
		wxBitmapButton* BitmapButtonPosRand;
		wxSlider* SliderSy;
		//*)

	protected:

		//(*Identifiers(moObjectMotion)
		static const long ID_SLIDERTX;
		static const long ID_SLIDERTZ;
		static const long ID_SLIDERTY;
		static const long ID_TEXTCTRLTX;
		static const long ID_TEXTCTRLTY;
		static const long ID_SLIDERRZ;
		static const long ID_SLIDERSZ;
		static const long ID_SLIDERSY;
		static const long ID_TEXTCTRLRX;
		static const long ID_SLIDERRX;
		static const long ID_SLIDERRY;
		static const long ID_TEXTCTRLRY;
		static const long ID_SLIDERSX;
		static const long ID_PANEL6;
		static const long ID_TEXTCTRLTZ;
		static const long ID_PANEL9;
		static const long ID_PANELPOSITION;
		static const long ID_STATICBITMAP1;
		static const long ID_PANEL5;
		static const long ID_TEXTCTRLSZ;
		static const long ID_STATICBITMAP5;
		static const long ID_PANEL7;
		static const long ID_TEXTCTRLSY;
		static const long ID_STATICBITMAP3;
		static const long ID_PANEL4;
		static const long ID_TEXTCTRLSX;
		static const long ID_TEXTCTRLRZ;
		static const long ID_BITMAPBUTTONPOSCIRCULAR;
		static const long ID_BITMAPBUTTONPOSHOR;
		static const long ID_BITMAPBUTTONPOSVERT;
		static const long ID_BITMAPBUTTON8;
		static const long ID_BITMAPBUTTONPOSRAND;
		static const long ID_PANEL1;
		static const long ID_BITMAPBUTTONROTCIRCULAR;
		static const long ID_BITMAPBUTTONROTHOR;
		static const long ID_BITMAPBUTTONROTVER;
		static const long ID_BITMAPBUTTONROTDIAG;
		static const long ID_BITMAPBUTTONROTRAND;
		static const long ID_PANEL2;
		static const long ID_BITMAPBUTTONSCACIRCULAR;
		static const long ID_BITMAPBUTTONSCAHOR;
		static const long ID_BITMAPBUTTONSCAVER;
		static const long ID_BITMAPBUTTONSCADIAG;
		static const long ID_BITMAPBUTTONSCARAND;
		static const long ID_PANEL10;
		static const long ID_PANELTRANSLATE;
		//*)

	private:

		//(*Handlers(moObjectMotion)
		void OnTextCtrlTxText(wxCommandEvent& event);
		void OnTextCtrlTyText(wxCommandEvent& event);
		void OnTextCtrlTzText(wxCommandEvent& event);
		void OnTextCtrlSxText(wxCommandEvent& event);
		void OnTextCtrlSyText(wxCommandEvent& event);
		void OnTextCtrlSzText(wxCommandEvent& event);
		void OnTextCtrlRxText(wxCommandEvent& event);
		void OnTextCtrlRyText(wxCommandEvent& event);
		void OnTextCtrlRzText(wxCommandEvent& event);
		void OnSliderTxCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderTyCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderTzCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderSxCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderSyCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderSzCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderRxCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderRyCmdScrollThumbTrack(wxScrollEvent& event);
		void OnSliderRzCmdScrollThumbTrack(wxScrollEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnSliderRyCmdScroll(wxScrollEvent& event);
		void OnBitmapButton3Click(wxCommandEvent& event);
		void OnBitmapButton4Click(wxCommandEvent& event);
		void OnBitmapButton2Click(wxCommandEvent& event);
		void OnBitmapButtonMotionCircularClick(wxCommandEvent& event);
		void OnSliderRxCmdScroll(wxScrollEvent& event);
		void OnSliderRxCmdScroll1(wxScrollEvent& event);
		void OnBitmapButtonScaCircularClick(wxCommandEvent& event);
		void OnBitmapButtonRotCircularClick(wxCommandEvent& event);
		//*)

		moMobDescriptor   m_MobDescriptor;

		moValueDescriptor   m_ValueDescriptorTx;
		moValueDescriptor   m_ValueDescriptorTy;
		moValueDescriptor   m_ValueDescriptorTz;

		moValueDescriptor   m_ValueDescriptorSx;
		moValueDescriptor   m_ValueDescriptorSy;
		moValueDescriptor   m_ValueDescriptorSz;

		moValueDescriptor   m_ValueDescriptorRx;
		moValueDescriptor   m_ValueDescriptorRy;
		moValueDescriptor   m_ValueDescriptorRz;


		DECLARE_EVENT_TABLE()
};

#endif
