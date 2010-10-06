#include "moDirectorCore.h"

/// TODO arreglar: cerrar el proyecto y abrirlo de nuevo no funciona, explota
/// TODO **LISTO** cambio rapido: colapsar el arbol de parametros

/// TODO **LISTO** EffectLayerCtrl: prender, apagar el efecto, falta que refleje los cambios
/// TODO **LISTO** EffectLayerCtrl: controlar la transparencia y la velocidad con los sliders

/// TODO Console: pensar en colocar una funcion de callback dentro de la consola de moldeo para recibir las modificaciones hechas dentro de la misma consola

/// TODO Inspector: que automaticamente trate de reconocer si el efecto elegido tiene algun parametro para ser inspeccionado
/// TODO Inspector: al seleccionar una pagina del notebook o hacer foco, refrescará el control con los datos

/// TODO PanelTexture: que ejecute el cambio de shader, que se refleje

/// TODO ColorMotion: que se vea el color en el cuadradito

/// TODO **LISTO** ObjectMotion: que funcionen los sliders
/// TODO ObjectMotion: representar la funcion en una pequeña ventana en el costado

/// TODO FunctionPanel: agregar sliders... para controlar: fase, frecuencia y amplitud...
/// TODO FunctionPanel: representar la funcion en un pequeño cuadro en el costado


moDirectorCore::moDirectorCore() {
	m_pDirectorConsole = NULL;
	m_pDirectorIODeviceManager = NULL;
	m_pResourceManager = NULL;
}

moDirectorCore::~moDirectorCore() {
	if(m_pDirectorConsole!=NULL) {
		delete m_pDirectorConsole;
		m_pDirectorConsole = NULL;
	}
	if(m_pDirectorIODeviceManager!=NULL) {
		delete m_pDirectorIODeviceManager;
		m_pDirectorIODeviceManager = NULL;
	}
	if(m_pResourceManager!=NULL) {
		delete m_pResourceManager;
		m_pResourceManager = NULL;
	}
	m_pUserInterface = NULL;
}

bool
moDirectorCore::Init() {

    moText workpath = moFileManager::GetWorkPath();

	//conffilename.
	if ( m_Config.LoadConfig( "director.gmo" ) != MO_CONFIG_OK ) {
	    if ( !moFileManager::FileExists( "director.gmo" ) ) {
            GetDefinition();
            if (!m_Config.CreateDefault( "director.gmo" ))
                return false;
           	m_Config.GetParam(moText("installationpath")).GetValue(0).GetSubValue(0).SetText( m_ApplicationDescriptor.GetInstallationFullPath() );
           	if (m_Config.SaveConfig()!=MO_CONFIG_OK)
                return false;

	    } else return false;
	}

    moDefineParamIndex( CORE_INSTALLATIONPATH, moText("installationpath") );
    moDefineParamIndex( CORE_CONFIGURATIONPATH, moText("configurationpath") );
    moDefineParamIndex( CORE_PLUGINSPATH, moText("pluginspath") );
    moDefineParamIndex( CORE_LASTPROJECTS, moText("lastprojects") );
    moDefineParamIndex( CORE_OPENFILES, moText("openfiles") );
    moDefineParamIndex( CORE_AUTOSAVE, moText("autosave") );
    moDefineParamIndex( CORE_EXECUTIONS, moText("executions") );
    moDefineParamIndex( CORE_SPLASHSCREEN, moText("splashscreen") );
    moDefineParamIndex( CORE_3DLOGO, moText("3dlogo") );

/*
    wxString file1;
    m_Config.GetParam(moText("project1")).GetValue(0).GetSubValue(0).SetText( file1 );
    wxMessageBox(wxT(file1),wxT("Moldeo Director"));
*/
	return true;
}

void
moDirectorCore::SetUserInterface( moDirectorFrame* p_pUserInterface ) {

	m_pUserInterface = p_pUserInterface;

	if ( m_pDirectorConsole == NULL ) {
		m_pDirectorConsole = new moDirectorConsole();
		m_pDirectorConsole!=NULL ? Log(moText("Director console created.")) : LogError(moText("Director console couldn't be created.")) ;
	}

	if ( m_pDirectorIODeviceManager == NULL ) {
		m_pDirectorIODeviceManager = new moDirectorIODeviceManager();
		m_pDirectorIODeviceManager!=NULL ? Log(moText("Director IODeviceManager created.")) : LogError(moText("Director IODeviceManager couldn't be created.")) ;
	}

	if ( m_pResourceManager == NULL ) {
		m_pResourceManager = new moResourceManager();
		m_pResourceManager!=NULL ? Log(moText("Director Resource Manager created.")) : LogError(moText("Director Resource Manager couldn't be created.")) ;
	}

	if ( m_pUserInterface && m_pResourceManager && m_pDirectorConsole) {

		m_pUserInterface->SetDirectorCore( this );
		m_pUserInterface->SetIODeviceManager(m_pDirectorIODeviceManager);

		m_pDirectorConsole->SetResourceManager( m_pResourceManager );
		m_pDirectorConsole->SetIODeviceManager( m_pDirectorIODeviceManager );
		m_pDirectorConsole->SetDirectorCore( this );
		Log("Resources initialized.");
	} else {
		LogError("Couldn't initialize resources modules correctly, maybe more memory is needed.");
		ErrorMessage("The program will close");
		exit(1);
	}
}

void
moDirectorCore::SetPaths( moText p_installationpath ) {

    m_ApplicationDescriptor = moApplicationDescriptor( p_installationpath, p_installationpath + moText("/plugins") );

}

//=============================================================================================================================



//=========================================================================================================================
//NEW IDIRECTORACTIONS
//=========================================================================================================================

	moResourceManager*	moDirectorCore::GetResourceManager() {

		return m_pResourceManager;

	}

	moDirectorStatus moDirectorCore::Preview() { return MO_DIRECTOR_STATUS_OK; }

	moDirectorStatus moDirectorCore::ConsoleLoop() {
	    return m_pDirectorConsole->ConsoleLoop();
    }

	void moDirectorCore::ViewSwapBuffers() {
	    if (m_pUserInterface)
            m_pUserInterface->ViewSwapBuffers();
    }

    moDirectorStatus
    moDirectorCore::SetView( int x, int y, int w, int h ) {
        return m_pDirectorConsole->SetView( x, y, w, h );
    }

    MO_HANDLE moDirectorCore::GetHandle() {
        return m_pUserInterface->GetHandle();
    }


	moDirectorStatus moDirectorCore::FullScreen( bool force) {
        return m_pUserInterface->FullScreen(force);
	}

	moDirectorStatus moDirectorCore::Play() {
        return m_pDirectorConsole->Play();
	}

	moDirectorStatus moDirectorCore::Pause() {
        return m_pDirectorConsole->Pause();
	}

	moDirectorStatus moDirectorCore::Stop() {
        return m_pDirectorConsole->Stop();
	}

	moDirectorStatus moDirectorCore::Seek( MOulong p_timecode ) {
        return m_pDirectorConsole->Seek(p_timecode);
	}

	moDirectorStatus moDirectorCore::FocusOutput() {
        return m_pUserInterface->FocusOutput();
	}

	moDirectorStatus moDirectorCore::SaveSession() {
        return m_pDirectorConsole->SaveSession();
	}

	moDirectorStatus moDirectorCore::SaveAll() {
	    return m_pDirectorConsole->SaveAll();
    }
	moDirectorStatus moDirectorCore::CloseAll() {
        return m_pUserInterface->CloseAll();
    }

	moDirectorStatus moDirectorCore::CloseApp() {
        m_pUserInterface = NULL;
        return MO_DIRECTOR_STATUS_OK;
    }

    void moDirectorCore::LoadPlugins( moPluginDefinitions& rPluginDefs, moText plugindir, moMoldeoObjectType mobjecttype ) {

        moDirectory DirEffects;
        bool bDebug = true;
        moText PluginName;

        //PREEFFECTS
        DirEffects.Open( plugindir, moText("/*.dll") );
        if (DirEffects.Exists()) {

            moFile* pFile = NULL;
            moText FileNameEnd;

            pFile = DirEffects.FindFirst();

            if (pFile!=NULL)
                Log( moText("File founded") );

            while(pFile!=NULL) {

                FileNameEnd = pFile->GetFileName();
                PluginName = pFile->GetFileName();
                FileNameEnd.Right(2);
                bDebug = ( FileNameEnd==moText("_d") );
                #ifndef MO_WIN32
                PluginName.Right( PluginName.Length() - 3 );
                #endif
                if (bDebug) PluginName.Left( PluginName.Length() - 3 );


                if ( ( pFile->GetExtension()==moText(".dll") || pFile->GetExtension()==moText(".so") ) && !bDebug ) {
                    rPluginDefs.Add( moPluginDefinition( PluginName, pFile->GetCompletePath(), mobjecttype ) );
                }
                Log( pFile->GetFileName() );
                pFile = DirEffects.FindNext();
            }
        } else LogError( moText("Directory doesn´t exists:")+(moText)plugindir );

    }

	moApplicationDescriptor moDirectorCore::GetApplicationDescriptor() {

        //actualizar lista de plugins:
        moText pluginsfullpath("MODULESDIR"); // = m_ApplicationDescriptor.GetPluginsFullPath();

        moPluginDefinitions& rPluginDefs( m_ApplicationDescriptor.GetPluginDefinitions());

        Log( moText("Checking plugins") );
        //recorrer los plugins en busca de: dll o so
        //lo interesante sería que la definición de los plugins se complete a su vez
        //...

        //pluginsfullpath + moText("/preeffects");
        moDirectory DirEffects;

        rPluginDefs.Empty();

        bool bDebug = true;
        moText PluginName;

        //PREEFFECTS
        LoadPlugins( rPluginDefs, pluginsfullpath + moText("/preeffects"), MO_OBJECT_PREEFFECT);

        //EFFECTS
        LoadPlugins( rPluginDefs, pluginsfullpath + moText("/effects"), MO_OBJECT_EFFECT);

        //POSTEFFECTS
        LoadPlugins( rPluginDefs, pluginsfullpath + moText("/posteffects"), MO_OBJECT_POSTEFFECT);

        //IODEVICES
        LoadPlugins( rPluginDefs, pluginsfullpath + moText("/iodevices"), MO_OBJECT_IODEVICE);

        //RESOURCES
        LoadPlugins( rPluginDefs, pluginsfullpath + moText("/resources"), MO_OBJECT_RESOURCE);

        moApplicationDescriptor pAppDes;
        pAppDes = m_ApplicationDescriptor;
        return pAppDes;

    }

//================================================================
//Project
//================================================================

	moDirectorStatus moDirectorCore::NewProject( moProjectDescriptor p_projectdescriptor ) {

        //copiar los archivos a  la carpeta

        /*
        wxString moldeopathinstall = moText2Wx( m_ApplicationDescriptor.GetInstallationFullPath() );
        wxString templaterelpath( _T("../../data/") );

        wxString templatepath  = moldeopathinstall + templaterelpath;

        moDirectory directory( moWx2Text(templatepath) );

        if ( !directory.Exists() )
        {
            ErrorMessage(moText("Error: el directorio no se pudo abrir > ") + moWx2Text(templatepath) );
            return MO_DIRECTOR_STATUS_ERROR;
        } else {
            */

            Log( moText("Creating project:") + p_projectdescriptor.GetFullConfigName() );

            //copiar los archivos al nuevo directorio... o crearlos desde cero????
            return m_pDirectorConsole->NewProject(p_projectdescriptor);


        //}



    }

	moDirectorStatus moDirectorCore::OpenProject( moProjectDescriptor p_projectdescriptor ) {
		return m_pDirectorConsole->OpenProject( p_projectdescriptor );
	}

	moDirectorStatus moDirectorCore::CloseProject() {
		if(m_pDirectorConsole->CloseProject() == MO_DIRECTOR_STATUS_OK) {
			return MO_DIRECTOR_STATUS_OK;
		}

		return MO_DIRECTOR_STATUS_ERROR;
	}

	moDirectorStatus moDirectorCore::SaveProject() {
        return m_pDirectorConsole->SaveProject();
    }

	moDirectorStatus moDirectorCore::SaveAsProject( moText p_configname, moText p_configpath ) { return MO_DIRECTOR_STATUS_OK; }

	moDirectorStatus moDirectorCore::ProjectUpdated( moProjectDescriptor p_projectdescriptor ) {

		return m_pUserInterface->ProjectUpdated( p_projectdescriptor );

	}

	moDirectorStatus moDirectorCore::SetProject( moProjectDescriptor p_projectdescriptor ) { return MO_DIRECTOR_STATUS_OK; }

	moProjectDescriptor moDirectorCore::GetProject() {
		return m_pDirectorConsole->GetProject();
	}

	moDirectorStatus moDirectorCore::ReloadProject() { return MO_DIRECTOR_STATUS_OK; }

	moDirectorStatus moDirectorCore::ProjectPreview( ) {
		return m_pUserInterface->ProjectPreview();
	}
	moDirectorStatus moDirectorCore::EffectPreview( MOint p_n ) { return MO_DIRECTOR_STATUS_OK; }

    moMobDescriptors moDirectorCore::GetMobDescriptors() {
            return m_pDirectorConsole->GetMobDescriptors();
    }


//================================================================
//Resources
//================================================================


    moResourceDescriptor moDirectorCore::GetResourceDescriptor( moResourceDescriptor p_ResourceDescriptor ) {
        return m_pDirectorConsole->GetResourceDescriptor( p_ResourceDescriptor );
    }

    moResourceDescriptors moDirectorCore::GetResourceDescriptors(  moResourceType p_ResourceType  ) {
        return m_pDirectorConsole->GetResourceDescriptors( p_ResourceType );
    }


//================================================================
//MOB Moldeo Object
//================================================================

moDirectorStatus moDirectorCore::NewMob( moMobDescriptor p_MobDesc ) {

    return m_pDirectorConsole->NewMob( p_MobDesc );

}

moDirectorStatus moDirectorCore::OpenMob( moMobDescriptor p_MobDesc ) {
    /**
    el core se fija que este archivo de configuracion no exista dentro de la
    carpeta actual del proyecto [conflicto al querer ser incluido]
    al menos que se trate del archivo en cuestión
     */

    //si el archivo no se encuentra dentro de la carpeta de nuestro proyecto es que lo tenemos que importar...

    //si ya se encuentra dentro de nuestro proyecto simplemente lo abrimos

    return m_pDirectorConsole->OpenMob( p_MobDesc );

}

moDirectorStatus moDirectorCore::ImportMob( moText p_filename ) {
    /**
    el core se fija que este archivo de configuracion no exista dentro de la
    carpeta actual del proyecto [conflicto al querer ser incluido]
    al menos que se trate del archivo en cuestión
     */

    //si el archivo no se encuentra dentro de la carpeta de nuestro proyecto es que lo tenemos que importar...

    //si ya se encuentra dentro de nuestro proyecto simplemente lo abrimos

    return m_pDirectorConsole->ImportMob( p_filename );

}


//remove from child frame List, and unload from SessionProject...
moDirectorStatus
moDirectorCore::CloseMob( moMobDescriptor p_MobDescriptor ) {

	return m_pDirectorConsole->CloseMob( p_MobDescriptor );

}

moDirectorStatus moDirectorCore::ReloadMob( moMobDescriptor p_MobDesc ) { return MO_DIRECTOR_STATUS_OK; }


moDirectorStatus moDirectorCore::EditMob( moMobDescriptor p_MobDescriptor ) {

	Log( moText("Opening MOB object")+(moText)p_MobDescriptor.GetMobDefinition().GetConfigName());

	return m_pUserInterface->EditMob( p_MobDescriptor );
}


	moDirectorStatus moDirectorCore::SaveMob( moMobDescriptor p_MobDesc ) {
	    return m_pDirectorConsole->SaveMob( p_MobDesc );
    }

	moDirectorStatus moDirectorCore::DeleteMob( moMobDescriptor p_MobDesc ) {

	    return m_pDirectorConsole->DeleteMob( p_MobDesc );

    }

	moMobDescriptor moDirectorCore::GetMob( moMobDescriptor p_MobDesc ) {
		return m_pDirectorConsole->GetMob(p_MobDesc);
	}

	moDirectorStatus moDirectorCore::SetMob( moMobDescriptor p_MobDesc ) {

        #ifdef _DEBUG
   		moText fxname = p_MobDesc.GetMobDefinition().GetLabelName();
		moText mobstext = moText(" alpha =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().alpha );
		mobstext+= moText(" tint =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().tint );
		mobstext+= moText(" tintr =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().tintr );
		mobstext+= moText(" tintg =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().tintg );
		mobstext+= moText(" tintb =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().tintb );
		mobstext+= moText(" tintc =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().tintc );
		mobstext+= moText(" tints =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().tints );
		mobstext+= moText("tempo.ang =>") + (moText)FloatToStr( p_MobDesc.GetState().GetEffectState().tempo.delta );

		Log( moText("For MOB: ") + (moText)fxname + moText(" setting state ::") + (moText)mobstext );
        #endif
	    return m_pDirectorConsole->SetMob( p_MobDesc );
    }

	moDirectorStatus moDirectorCore::MobUpdated( moMobDescriptor p_MobDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::AddMobToProject( moMobDescriptor p_MobDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::RemoveMobToProject( moMobDescriptor p_MobDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::MoveMobInProject( moMobDescriptor p_MobDesc ) { return MO_DIRECTOR_STATUS_OK; }

//================================================================
//PARAMETERS
//================================================================

	moDirectorStatus moDirectorCore::NewParameter( moParameterDescriptor p_ParameterDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::InsertParameter( moParameterDescriptor p_ParameterDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::MoveParameter( moParameterDescriptor p_ParameterDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::EditParameter( moParameterDescriptor p_ParameterDesc ) {
	    m_pUserInterface->EditParameter( p_ParameterDesc );
    }
	moDirectorStatus moDirectorCore::SaveParameter( moParameterDescriptor p_ParameterDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::SetParameter( moParameterDescriptor p_ParameterDesc ) {
	    return m_pDirectorConsole->SetParameter( p_ParameterDesc );
    }
	moParameterDescriptor moDirectorCore::GetParameter( moParameterDescriptor p_ParameterDesc ) {
	    return moParameterDescriptor();
    }
	moDirectorStatus moDirectorCore::DeleteParameter( moParameterDescriptor p_ParameterDesc ) { return MO_DIRECTOR_STATUS_OK; }
	moDirectorStatus moDirectorCore::ParameterUpdated( moParameterDescriptor p_ParameterDesc ) {
	    return m_pUserInterface->ParameterUpdated( p_ParameterDesc );
    }
	moDirectorStatus moDirectorCore::ReloadParameter( moParameterDescriptor p_ParameterDesc ) {
	    return MO_DIRECTOR_STATUS_OK;
    }

	moParameterDescriptors  moDirectorCore::GetParameterDescriptors( moMobDescriptor p_MobDesc ) {
	    return m_pDirectorConsole->GetParameterDescriptors(p_MobDesc);
    }


//================================================================
// VALUES
//================================================================

	moValueDescriptors  moDirectorCore::GetValueDescriptors( moParameterDescriptor p_ParamDesc ) {
	    return m_pDirectorConsole->GetValueDescriptors( p_ParamDesc );
    }


	moDirectorStatus moDirectorCore::NewValue( moValueDescriptor p_ValueDesc ) {
	    return MO_DIRECTOR_STATUS_OK;
    }
	moDirectorStatus moDirectorCore::InsertValue( moValueDescriptor p_ValueDesc ) {
	    return m_pDirectorConsole->InsertValue( p_ValueDesc );
    }
	moDirectorStatus moDirectorCore::EditValue( moValueDescriptor p_ValueDesc ) {
	    return m_pUserInterface->EditValue( p_ValueDesc );
    }
	moDirectorStatus moDirectorCore::SaveValue( moValueDescriptor p_ValueDesc ) {
	    //agregar cambios a la lista de UNDO's

	    //
	    return m_pDirectorConsole->SaveValue( p_ValueDesc );

	    //return MO_DIRECTOR_STATUS_OK;
    }
	moValueDescriptor moDirectorCore::GetValue( moValueDescriptor p_ValueDesc ) {
	    return m_pDirectorConsole->GetValue( p_ValueDesc );
    }
	moDirectorStatus moDirectorCore::SetValue( moValueDescriptor p_ValueDesc ) {

		//agregar cambios a la lista de UNDO's
		moText paramname = p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetName();
		moText valuestext = "";
		for( int i=0; i<(int)p_ValueDesc.GetValue().GetSubValueCount(); i++ ) {
		    valuestext+= moText("[")+(moText)+IntToStr(i)+moText("]") + (moText)p_ValueDesc.GetValue().GetSubValue(i).ToText();
        }

		Log( moText("For param: ") + (moText)paramname + moText(" setting value [:") + IntToStr( p_ValueDesc.GetValueIndex().m_ValueIndex ) + moText("] :") + (moText)valuestext );

        return m_pDirectorConsole->SetValue( p_ValueDesc );

    }
	moDirectorStatus moDirectorCore::DeleteValue( moValueDescriptor p_ValueDesc ) {
        return m_pDirectorConsole->DeleteValue( p_ValueDesc );
    }
	moDirectorStatus moDirectorCore::ValueUpdated( moValueDescriptor p_ValueDesc ) {

	    /*
	    if ( ! p_ValueDesc.GetValueDefinition().IsValid() ) {
	        LogError( moText("moDirectorCore::ValueUpdated() ValueDefinition is invalid ") );
        } else {
            if ( ! p_ValueDesc.GetParamDescriptor().GetParamDefinition().IsValid() ) {
                LogError( moText("moDirectorCore::ValueUpdated() ParamDefinition is invalid ") );
            } else {
                if ( ! p_ValueDesc.GetParamDescriptor().GetMobDescriptor().GetMobDefinition().IsValid() ) {
                    LogError( moText("moDirectorCore::ValueUpdated() MobDefinition is invalid ") );
                }
            }
        }
        */

	    moDirectorStatus res = m_pUserInterface->ValueUpdated( p_ValueDesc );
	    if (res!=MO_DIRECTOR_STATUS_OK) {
	        moText moberror = p_ValueDesc.GetParamDescriptor().GetMobDescriptor().GetMobDefinition().GetLabelName();
	        moText paramerror = p_ValueDesc.GetParamDescriptor().GetParamDefinition().GetName();
	        moText valueerror = p_ValueDesc.GetValue().GetSubValue(0).ToText();
            LogError(   moText("moDirectorCore::ValueUpdated() Couldn't set the value: mob: ") +
                        (moText) moberror +
                        moText(" param: ") +
                        (moText) paramerror +
                        moText(" subvalue 0:") +
                        (moText) valueerror ) ;
	    }
	    return res;
    }
	moDirectorStatus moDirectorCore::ReloadValue( moValueDescriptor p_ValueDesc ) {
	    return MO_DIRECTOR_STATUS_OK;
    }

//===============================================================
// LOGS
//===============================================================

	void moDirectorCore::Log( moText p_message ) {

		m_pUserInterface->Log( p_message );
		//m_pUserInterface->SetStatusText( w );
	}
	void moDirectorCore::LogError( moText p_message ) {

		m_pUserInterface->LogError( p_message );

	}
	void moDirectorCore::ShowMessage( moText p_message ) {

		wxString msg =wxString(p_message, wxConvUTF8);

		wxMessageBox( msg );

	}

	bool moDirectorCore::ConfirmMessage( moText p_message ) {

		wxString msg =wxString(p_message, wxConvUTF8);

		int answer = wxMessageBox( msg, wxT("Confirm"),
                            wxYES_NO | wxCANCEL | wxICON_QUESTION );

		if (answer == wxYES) {
			return(true);
		} else {
			return(false);
		}

	}

	void moDirectorCore::AlertMessage( moText p_message ) {

		wxString msg =wxString(p_message, wxConvUTF8);

		int answer = wxMessageBox( msg, wxT("Alert!"),
                            wxOK | wxICON_EXCLAMATION );

	}

	void moDirectorCore::ErrorMessage( moText p_message ) {

		wxString msg =wxString(p_message, wxConvUTF8);

		int answer = wxMessageBox( msg, wxT("Error!"),
                            wxOK | wxICON_ERROR );

	}


//=============================================================================================================================

moConfigDefinition *
moDirectorCore::GetDefinition( moConfigDefinition *p_configdefinition ) {

	if ( p_configdefinition==NULL ) {
		p_configdefinition = m_Config.GetConfigDefinition();
	}

    p_configdefinition->Set( "moldeodirector", "moldeoguicore" );
    p_configdefinition->Add( moText("installationpath"), MO_PARAM_TEXT );
    p_configdefinition->Add( moText("configurationpath"), MO_PARAM_TEXT );
    p_configdefinition->Add( moText("pluginspath"), MO_PARAM_TEXT );
    p_configdefinition->Add( moText("lastprojects"), MO_PARAM_TEXT );
    p_configdefinition->Add( moText("openfiles"), MO_PARAM_TEXT );
    p_configdefinition->Add( moText("autosave"), MO_PARAM_TEXT );
    p_configdefinition->Add( moText("executions"), MO_PARAM_NUMERIC );
    p_configdefinition->Add( moText("splashscreen"), MO_PARAM_TEXTURE );
    p_configdefinition->Add( moText("3dlogo"), MO_PARAM_OBJECT );

	//p_configdefinition->Add( moText("inlet"), MO_PARAM_INLET );
	//p_configdefinition->Add( moText("outlet"), MO_PARAM_OUTLET );
	return p_configdefinition;
}

void
moDirectorCore::LoadDefinition() {

	GetDefinition();

	moParamDefinitions *pdefinitions = m_Config.GetConfigDefinition()->GetParamDefinitions();

	for( MOuint i=0; i < pdefinitions->Count(); i++ ) {
		pdefinitions->Get(i).SetIndex( m_Config.GetParamIndex( pdefinitions->Get(i).GetName() ));
	}

}


