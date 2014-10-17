#include "moSessionProject.h"

moSessionProject::moSessionProject() {

}

moSessionProject::~moSessionProject() {

}


void moSessionProject::Init() {

	int i;

	m_pDirectorCore = NULL;

	for( i=0; i<MO_OBJECT_TYPES; i++) {
		m_pMobs[i]=NULL;
	}


	return;
}

void moSessionProject::Finish() {
	return;
}


void
moSessionProject::SetDirectorCore( moDirectorCore* p_pDirectorCore ) {

	m_pDirectorCore = p_pDirectorCore;
	SetNextActionHandler((moIDirectorActions*)m_pDirectorCore);

}



//=========================================================================================================================
//NEW IDIRECTORACTIONS
//=========================================================================================================================


//================================================================
//Project
//================================================================


moDirectorStatus
moSessionProject::NewProject( moProjectDescriptor p_ProjectDescriptor )  {//create a console.cfg file with their effects.cfg

	return MO_DIRECTOR_STATUS_OK;
}


moDirectorStatus
moSessionProject::OpenProject( moProjectDescriptor p_ProjectDescriptor )  {//load a console.cfg file with their effects.cfg

	m_ProjectDescriptor = p_ProjectDescriptor;

	if( m_ConsoleConfig.LoadConfig( p_ProjectDescriptor.GetFullConfigName() ) == MO_CONFIG_OK) {

		/*
		wxFileName xfname( wxString((char*) p_config ) );
		wxString xstring;
		xstring = xfname.GetPath( wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR	);
		const char *cfilename =(const char *) xstring;

		m_ProjectPath =(char*)cfilename;
		m_ProjectFullName = p_config;
		*/

		LoadMobs();

		m_pDirectorCore->ProjectUpdated( m_ProjectDescriptor );//notice the core that the file is loaded

	}

	return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moSessionProject::CloseProject() {

	m_ConsoleConfig.DeleteConfig();

	this->UnloadMobs();

	/*
	m_pDirectorCore->ProjectUpdated( m_ProjectDescriptor );
	*/

	return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moSessionProject::SaveProject() { //save a console.cfg file with their effects.cfg

	return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moSessionProject::SaveAsProject( moText p_configname, moText p_configpath ) { //save a console.cfg file with their effects.cfg

	return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moSessionProject::SetProject( moProjectDescriptor p_projectdescriptor ) {
	return MO_DIRECTOR_STATUS_OK;
}

moProjectDescriptor
moSessionProject::GetProject() {
	return m_ProjectDescriptor;
}

moDirectorStatus
moSessionProject::ReloadProject() {

	return MO_DIRECTOR_STATUS_OK;
}

//================================================================
//MOB Moldeo Object
//================================================================
/*
moDirectorStatus
moSessionProject::CloseConfig( moText p_configname ) {

	MOint i;
	MOint verif;

	for( i=0; i < m_nEffects; i++) {
		if(m_pEffects[i].IsConfigLoaded()) {
			if(m_pEffects[i].GetConfigFullName()==p_configname) {
				m_pEffects[i].UnloadConfig();
				return MO_DIRECTOR_STATUS_OK;
			}
		}
	}
	for( i=0; i < m_nPreEffects; i++) {
		if(m_pPreEffects[i].IsConfigLoaded()) {
			if(m_pPreEffects[i].GetConfigFullName()==p_configname) {
				m_pPreEffects[i].UnloadConfig();
				return MO_DIRECTOR_STATUS_OK;
			}
		}
	}
	for( i=0; i < m_nPostEffects; i++) {
		if(m_pPostEffects[i].IsConfigLoaded()) {
			if(m_pPostEffects[i].GetConfigFullName()==p_configname) {
				m_pPostEffects[i].UnloadConfig();
				return MO_DIRECTOR_STATUS_OK;
			}
		}
	}
	for( i=0; i < m_nMasterEffects; i++) {
		if(m_pMasterEffects[i].IsConfigLoaded()) {
			if(m_pMasterEffects[i].GetConfigFullName()==p_configname) {
				m_pMasterEffects[i].UnloadConfig();
				return MO_DIRECTOR_STATUS_OK;
			}
		}
	}
	for( i=0; i < m_nIODevices; i++) {
		if(m_pIODevices[i].IsConfigLoaded()) {
			if(m_pIODevices[i].GetConfigFullName()==p_configname) {
				m_pIODevices[i].UnloadConfig();
				return MO_DIRECTOR_STATUS_OK;
			}
		}
	}
	return MO_DIRECTOR_STATUS_OK;
}
*/


//================================================================
//MOB Moldeo Object
//================================================================

	moDirectorStatus
	moSessionProject::OpenMob( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::CloseMob( moMobDescriptor p_MobDesc ) {

        //Aqui hay que ver si vale la pena descargar el config.
        //En definitiva si solo cargamos los configs de aquellos objetos que visualizamos, o que esten activos
        //en principio es mejor que sea todo en tiempo real, pero esta seria una opcion para cargar más rapidamente el proyecto
        //algo asi como cargar el proyecto offline... u online...
        /*
		if ( 0<=p_MobDesc.GetIndex() && p_MobDesc.GetIndex()< m_ProjectDescriptor.GetMobsCount(p_MobDesc.GetType())) {

			if( m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].IsConfigLoaded() ) {
				m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].UnloadConfig();
				return MO_DIRECTOR_STATUS_OK;
			} else {
				return MO_DIRECTOR_STATUS_ERROR;
			}
		} else return MO_DIRECTOR_STATUS_ERROR;
		*/
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::ReloadMob( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::NewMob( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::EditMob( moMobDescriptor p_MobDesc ) {

		MOint verif;

		if ( 0<=p_MobDesc.GetIndex() && p_MobDesc.GetIndex()< m_ProjectDescriptor.GetMobsCount(p_MobDesc.GetType())) {

			if( m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].IsConfigLoaded() ) {
				return MO_DIRECTOR_STATUS_CONFIG_ALREADY_LOADED;
			} else {
				m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].LoadConfig();
			}

			verif = m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].IsConfigLoaded();

			if(!verif) {
				moText errmsg = "Couldn´t load effect's config:";
				errmsg+= p_MobDesc.GetFullConfigName();
				ShowMessage( errmsg );
				return MO_DIRECTOR_STATUS_CONFIG_ERROR;
			}
			return MO_DIRECTOR_STATUS_OK;
		} else return MO_DIRECTOR_STATUS_ERROR;

	}

	moDirectorStatus
	moSessionProject::SaveMob( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::DeleteMob( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moMobDescriptor
	moSessionProject::GetMob( moMobDescriptor p_MobDesc ) {
		if ( 0<=p_MobDesc.GetIndex() && p_MobDesc.GetIndex()< m_ProjectDescriptor.GetMobsCount(p_MobDesc.GetType())) {
			return m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].GetMobDescriptor();
		} else return moMobDescriptor();
	}

	moDirectorStatus
	moSessionProject::SetMob( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::AddMobToProject( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::RemoveMobToProject( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moSessionProject::MoveMobInProject( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}


//=========================================================================================================================
//
//=========================================================================================================================


void
moSessionProject::LoadMobs() {

		moText namefull;
		moText name;
		moText namecfg;
		MOint efx[5];
		MOint i,m;

		efx[0] = m_ConsoleConfig.GetParamIndex("devices");
		efx[1] = m_ConsoleConfig.GetParamIndex("preeffect");
		efx[2] = m_ConsoleConfig.GetParamIndex("effect");
		efx[3] = m_ConsoleConfig.GetParamIndex("posteffect");
		efx[4] = m_ConsoleConfig.GetParamIndex("mastereffect");

		/*m_ProjectDescriptor.SetMobsCount( m_ConsoleConfig.GetValuesCount(efx[0]),
			m_ConsoleConfig.GetValuesCount(efx[1]),
			m_ConsoleConfig.GetValuesCount(efx[2]),
			m_ConsoleConfig.GetValuesCount(efx[3]),
			m_ConsoleConfig.GetValuesCount(efx[4]) );

		for( i=0; i<MO_OBJECT_TYPES; i++) {

			if ( m_pMobs[i]!=NULL ) {
				delete [] m_pMobs[i];
				m_pMobs[i] = NULL;
			}

			if ( m_pMobs[i]==NULL ) {
				int count = m_ProjectDescriptor.GetMobsCount((enumMobType)(i));

				if (count>0) {
					m_pMobs[i] = new moMobConfig [ count ];

					m_ConsoleConfig.SetCurrentParamIndex( efx[i] );

					m_ConsoleConfig.FirstValue();

					for( m=0; m < count; m++) {

						name = m_ConsoleConfig.GetParam().GetValue().GetSubValue(MO_CFG_EFFECT).Text();

						if ( name == moText("nil") ) {

							name = "nil";
							namefull = "nil";
							namecfg = "nil";

						} else {

							namecfg = m_ConsoleConfig.GetParam().GetValue().GetSubValue(MO_CFG_EFFECT_CONFIG).Text();
							namecfg+= ".cfg";
							namefull = m_ProjectDescriptor.GetConfigPath() + (moText)namecfg;

						}

						moMobDescriptor MOB((enumMobType)(i),m);

						MOB.Set( name, moText(""), namecfg, namefull );

						m_pMobs[i][m].Init( MOB );

						m_ConsoleConfig.NextValue();
					}
				}
			}
		}*/

}

void
moSessionProject::UnloadMobs() {

	MOint i,m;

/*	for( i=0; i<MO_MOB_TYPES ; i++) {
		for( m=0; m < m_ProjectDescriptor.GetMobsCount(((enumMobType)i)); m++) {
			m_pMobs[i][m].UnloadConfig();
		}

		if ( m_pMobs[i]!=NULL ) {
			delete [] m_pMobs[i];
			m_pMobs[i] = NULL;
		}
	}

	m_ProjectDescriptor.Set( moText(""),moText(""));

	m_ProjectDescriptor.SetMobsCount(0,0,0,0,0);
	*/

}
