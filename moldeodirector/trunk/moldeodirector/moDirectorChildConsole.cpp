#include "moDirectorChildConsole.h"

moDirectorChildConsole::moDirectorChildConsole() : moDirectorConsole() {

	m_EffectConfigName = "";
	m_EffectName = "";
}

moDirectorChildConsole::~moDirectorChildConsole() {
/*
	m_pGLCanvas = NULL;
	m_timer.Stop();*/
	//moDirectorConsole::~moDirectorConsole();

}


MOboolean moDirectorChildConsole::Init( moText p_effectname,
		moText p_effectconfigname,
        moText p_apppath,
		moText p_datapath,
		moText p_consoleconfig,
		moIODeviceManager* p_pIODeviceManager,
		moResourceManager *p_pResourceManager,
		MOint p_render_to_texture_mode,
		MOint p_screen_width, MOint p_screen_height,
		MOint p_render_width, MOint p_render_height ) {

	wxFileName xfname( wxString(moText2Wx( p_effectconfigname )) );
	wxString xstring;
	xstring = xfname.GetName();
	const char *cfilename =(const char *) xstring.c_str();

	m_EffectConfigName =(char*)cfilename;
	m_EffectName = p_effectname;

	return Init( p_apppath,
        p_datapath,
		p_consoleconfig,
		p_pIODeviceManager,
		p_pResourceManager,
		p_render_to_texture_mode,
		p_screen_width, p_screen_height,
		p_render_width, p_render_height);
}

MOboolean
moDirectorChildConsole::Init(
                        moText p_apppath,
                        moText p_datapath,
						moText p_consoleconfig,
						moIODeviceManager* p_pIODeviceManager,
						moResourceManager *p_pResourceManager,
		               MOint p_render_to_texture_mode,
					   MOint p_screen_width, MOint p_screen_height,
					   MOint p_render_width, MOint p_render_height ) {

	moText text;
	int i=-1,verif;
	//int a,b;

	idebug = -1;
	iligia = -1;
	iborrado = -1;

	srand( time(NULL) );

	if(m_EffectName==moText("") || m_EffectConfigName==moText("")) {
		Finish();
		return false;
	}

	if( p_pIODeviceManager == NULL ) {
		m_bIODeviceManagerDefault = true;
		m_pIODeviceManager = new moIODeviceManager();
	} else {
		m_bIODeviceManagerDefault = false;
		m_pIODeviceManager = p_pIODeviceManager;
	}

	m_EffectManager.Init();

	//INITIALIZING FIXED COMPONENTS
	m_ConsoleState.Init();

	verif = m_Config.LoadConfig( p_consoleconfig ) ;//este parametro debe pasarse desde fuera
	if(verif != MO_CONFIG_OK) {
	    Finish();
		//then
		return false;
	} else SetConfigName(p_consoleconfig);

	InitResources(  p_pResourceManager,
					p_apppath,
					p_datapath,
					m_Config,
					p_render_to_texture_mode,
					p_screen_width, p_screen_height,
					p_render_width, p_render_height );

	//NEW CODE FOR CHILD, ONE EFFECT ONLY

	// 0: Load Ressources
	LoadResources();
	// 1: Load IODevices: same than console.cfg
	LoadIODevices();
	// 2: Load MasterEffects
	LoadMasterEffects();

	moText fxname, cfname, lblname;
	// 3: Load PreEffects Erase
	fxname = moText("erase");
	cfname = moText("_erase");
	lblname = moText("erase");
	moPreEffect* ppreeffect = (moPreEffect*)m_EffectManager.NewEffect( fxname, cfname, lblname,  MO_OBJECT_PREEFFECT, -1, -1);
	if (ppreeffect) {
		m_MoldeoObjects.Add( (moMoldeoObject*) ppreeffect );
		ppreeffect->SetResourceManager( m_pResourceManager );
		if ( ppreeffect->GetName() == moText("erase") ) {
				iborrado = i;
				printf("erase");
				ppreeffect->Init();
				ppreeffect->Activate();
		}
	} else return false;

	// 4: Load Effect one: the only one...
	fxname = m_EffectName;
	cfname = m_EffectConfigName;
	lblname = m_EffectConfigName;
	moEffect* peffect = (moEffect*)m_EffectManager.NewEffect( fxname, cfname, lblname,  MO_OBJECT_EFFECT, -1, -1);
	if (peffect) {
		m_MoldeoObjects.Add( (moMoldeoObject*) peffect );
		peffect->SetResourceManager( m_pResourceManager );
	} else return false;

	m_ConsoleState.m_nAllEffects = m_EffectManager.AllEffects().Count();

	InitializeAllEffects();

	StartMasterEffects();

	LoadConnections();

	return true;

}
