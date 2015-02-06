#include "moDirectorConsole.h"
#include "moTextureFilterIndex.h"

BEGIN_EVENT_TABLE( moDirectorConsole, wxEvtHandler)
  EVT_TIMER( TICKS_ID, moDirectorConsole::OnTimer)
END_EVENT_TABLE()

#define FRAME_MILIS 16

moDirectorConsole::moDirectorConsole() : moConsole() {

	m_pDirectorCore = NULL;
	m_timerticks = 0;
	previewreset = false;
	previewreset2 = false;

}

moDirectorConsole::~moDirectorConsole() {

    Finish();

}

MOboolean moDirectorConsole::Finish() {

	m_bInitialized = false; //assuring that Draw isnt called
	m_timer.Stop();
	return moConsole::Finish();

}

void
moDirectorConsole::SetDirectorCore( moDirectorCore* p_pDirectorCore ) {

	m_pDirectorCore = p_pDirectorCore;
	SetNextActionHandler((moIDirectorActions*)m_pDirectorCore);
    m_timer.SetOwner( this, TICKS_ID);
	m_timer.Start(FRAME_MILIS);
}

moMoldeoObject*
moDirectorConsole::GetObject( moMobDescriptor p_MobDesc ) {

    moMoldeoObject* pMOB = NULL;

    MOint idx = p_MobDesc.GetMobDefinition().GetMobIndex().GetValueIndex();
    switch( p_MobDesc.GetMobDefinition().GetType() ) {
        case MO_OBJECT_PREEFFECT:
            if (idx>-1) pMOB = (moMoldeoObject*) m_EffectManager.PreEffects().GetRef(idx);
            break;
        case MO_OBJECT_EFFECT:
            if (idx>-1) pMOB = (moMoldeoObject*) m_EffectManager.Effects().GetRef(idx);
            break;
        case MO_OBJECT_POSTEFFECT:
            if (idx>-1) pMOB = (moMoldeoObject*) m_EffectManager.PostEffects().GetRef(idx);
            break;
        case MO_OBJECT_MASTEREFFECT:
            if (idx>-1) pMOB = (moMoldeoObject*) m_EffectManager.MasterEffects().GetRef(idx);
            break;
        case MO_OBJECT_IODEVICE:
            if (idx>-1) pMOB = (moMoldeoObject*) m_pIODeviceManager->IODevices().GetRef(idx);
            break;
        case MO_OBJECT_RESOURCE:
            idx = m_pResourceManager->GetResourceIndex( p_MobDesc.GetMobDefinition().GetLabelName() );
            pMOB = (moMoldeoObject*) m_pResourceManager->GetResource(idx);
            break;
        case MO_OBJECT_CONSOLE:
            pMOB = dynamic_cast<moMoldeoObject*>(this);
            break;

    }
    if (!pMOB)
        LogError( moText("moDirectorConsole::GetObject pMOB is NULL > idx = ") + IntToStr(idx) + moText(" Label:") + moText(p_MobDesc.GetMobDefinition().GetLabelName()) + moText(" Config:") + moText(p_MobDesc.GetMobDefinition().GetConfigName()) );
    return pMOB;

}

//=========================================================================================================================
//NEW IDIRECTORACTIONS
//=========================================================================================================================


//================================================================
//Project
//================================================================


moDirectorStatus
moDirectorConsole::NewProject( const moProjectDescriptor& p_ProjectDes )  {//create a console.cfg file with their effects.cfg

	//minimo: crear el archivo de consola .mol

	//crea las definiciones de parámetros
	GetDefinition();

	if ( m_Config.CreateDefault( p_ProjectDes.GetFullConfigName() ) ) {
	    m_Config.GetParam( "devices" ).DeleteValue(0);
	    m_Config.GetParam( "resources" ).DeleteValue(0);
	    m_Config.GetParam( "preeffect" ).DeleteValue(0);
	    m_Config.GetParam( "effect" ).DeleteValue(0);
	    m_Config.GetParam( "posteffect" ).DeleteValue(0);
	    m_Config.GetParam( "mastereffect" ).DeleteValue(0);

	    if ( m_Config.SaveConfig( p_ProjectDes.GetFullConfigName() ) == MO_CONFIG_OK ) {

            m_Config.UnloadConfig();

            ///...

            Log( moText(".mol default project file created") );

            return OpenProject( p_ProjectDes );
	    } else LogError( moText("Couldn't update mol file") );
    }

    m_pDirectorCore->LogError( moText("An error ocurred while creating mol file") );

    return MO_DIRECTOR_STATUS_ERROR;

}

#ifdef MO_LINUX
    //#include <gtk/gtk.h>
    //#include <gdk/gdkx.h>
#endif

moDirectorStatus
moDirectorConsole::OpenProject( const moProjectDescriptor& p_ProjectDes )  {//load a console.cfg file with their effects.cfg
	//es importante reinicializar
    CloseProject();

	if (m_pResourceManager)
        m_pResourceManager->Finish();

	if ( Initialized() ) {
	  m_ProjectDescriptor.SetState( moProjectDescriptor::STATE_CLOSING );
		if (Finish()) {
      m_ProjectDescriptor.SetState( moProjectDescriptor::STATE_CLOSED );
		}
	}

  wxString wxAppPath =wxGetCwd();

  MO_HANDLE pHandle;
  MO_DISPLAY pDisplay;

  pHandle = NULL;
  pDisplay = NULL;

  pHandle = GetHandle();

  #ifdef MO_LINUX
    //GtkWidget* gtkwidget = (GtkWidget*) pHandle;
    //Display* dpy = GDK_WINDOW_XDISPLAY( gtkwidget->window );
    //pDisplay = (MO_DISPLAY)dpy;
  #endif

  m_ProjectDescriptor.SetState( moProjectDescriptor::STATE_OPENING );

 	if( Init(   moWx2Text(wxAppPath),
              p_ProjectDes.GetConfigPath(),
              p_ProjectDes.GetFullConfigName(),
              m_pIODeviceManager,
              m_pResourceManager,
              //RENDERMANAGER_MODE_FRAMEBUFFER,
              //RENDERMANAGER_MODE_FRAMEBUFFER,
              RENDERMANAGER_MODE_NORMAL,
              //render to texture: MO_RENDER_TO_TEXTURE_FBSCREEN
              //RENDERMANAGER_MODE_NORMAL,
              400,300,400,300,
              /*MO_DEF_SCREEN_WIDTH, MO_DEF_SCREEN_HEIGHT,
              MO_DEF_RENDER_WIDTH, MO_DEF_RENDER_HEIGHT,*/
              pHandle,
              pDisplay

           )) {


        m_ProjectDescriptor.Set(
            p_ProjectDes.GetConfigPath(),
            p_ProjectDes.GetConfigName() );

        ///ahora actualizarmos el GUI
        m_ProjectDescriptor.SetState( moProjectDescriptor::STATE_OPENED );
        m_pDirectorCore->ProjectUpdated( m_ProjectDescriptor );


        ///========================================================================
        ///  ACTUALIZAMOS TODOS LOS VALORES: para aquellos objetos que lo necesiten
        ///========================================================================



        moMobDescriptors mMobs = GetMobDescriptors();

        for( MOuint i=0; i < mMobs.Count(); i++ ) {

            moMobDescriptor mMob = mMobs[i];

            moParameterDescriptors  pParams = GetParameterDescriptors( mMob );

            if ( (mMob.GetMobDefinition().GetType()!=MO_OBJECT_IODEVICE) &&
                 (mMob.GetMobDefinition().GetType()!=MO_OBJECT_RESOURCE) &&
                 (mMob.GetMobDefinition().GetType()!=MO_OBJECT_CONSOLE )

                  ) {

                for( int j=0; j<(int)pParams.Count(); j++ ) {

                    moParameterDescriptor pParam = pParams[j];

                    moValueIndex indx;
                    indx.m_ParamIndex = pParam.GetIndex();
                    indx.m_ValueIndex = pParam.GetIndexValue();

                    moValueDescriptor pValueDescriptor( pParam, indx );

                    pValueDescriptor = GetValue( pValueDescriptor );

                    ValueUpdated( pValueDescriptor );

                }

            }

        }

        previewreset = false;


		moText mode = m_Config[moR(CONSOLE_OUTPUTMODE)][MO_SELECTED][0].Text();

		if (mode==moText("AUTOPLAY")) {
            this->Play();
            m_pDirectorCore->ProjectPreview();
            //primera vez pone al tamaño del output definido en el config
            m_pDirectorCore->FocusOutput();
            //dos veces para posicionar la ventana en el segundo display
            m_pDirectorCore->FocusOutput();

            previewreset = true;
        }

        m_timer.Start(FRAME_MILIS);

        return MO_DIRECTOR_STATUS_OK;
	} else {
        LogError(moText("Couldn't init Console with current project"));
    }

	return MO_DIRECTOR_STATUS_ERROR;
}

moDirectorStatus
moDirectorConsole::CloseProject() {

	if ( Initialized() ) {
	  m_ProjectDescriptor.SetState( moProjectDescriptor::STATE_CLOSING );
		if ( Finish() ) {
		  ///pasamos el estado a cerrado
		  m_ProjectDescriptor.SetState( moProjectDescriptor::STATE_CLOSED );

		  return m_pDirectorCore->ProjectUpdated( m_ProjectDescriptor );

		} else return MO_DIRECTOR_STATUS_ERROR;
	}
  //m_timer.Stop();
	return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus
moDirectorConsole::SaveProject() { //save a console.cfg file with their effects.cfg

    if ( m_Config.SaveConfig() == MO_CONFIG_OK ) {
        ShowMessage( moText("Project saved succesfully.") );
        return MO_DIRECTOR_STATUS_OK;
    } else {
        ErrorMessage(moText("Failed to save project! Retry later."));
        return MO_DIRECTOR_STATUS_ERROR;
    }
}

moDirectorStatus
moDirectorConsole::SaveAsProject( moText p_configname, moText p_configpath ) { //save a console.cfg file with their effects.cfg

	return MO_DIRECTOR_STATUS_OK;
}


///modifica los valores del proyecto
moDirectorStatus
moDirectorConsole::SetProject( const moProjectDescriptor& p_projectdescriptor ) {
	return MO_DIRECTOR_STATUS_OK;
}

///devuelve el proyecto actual
const moProjectDescriptor&
moDirectorConsole::GetProject() {
	return m_ProjectDescriptor;
}

moDirectorStatus
moDirectorConsole::ReloadProject() {

	return MO_DIRECTOR_STATUS_OK;
}


moMobDescriptors moDirectorConsole::GetMobDescriptors() {
    //generar la lista de MobDescriptor de todo el proyecto:
    moMobDescriptors    mMobDescriptors;

    for( int i=0;  i < (int) m_MoldeoObjects.Count(); i++) {
        moMoldeoObject* pMOB = m_MoldeoObjects.GetRef(i);
        if (pMOB) {
            moEffect* pEffect = NULL;
            switch(pMOB->GetType()) {
                case MO_OBJECT_IODEVICE:

                    break;
                case MO_OBJECT_RESOURCE:

                    break;

                case MO_OBJECT_PREEFFECT:
                case MO_OBJECT_EFFECT:
                case MO_OBJECT_POSTEFFECT:
                case MO_OBJECT_MASTEREFFECT:
                    pEffect = (moEffect*) pMOB;
                    break;
            }

            moMobDescriptor mMobDescriptor( m_ProjectDescriptor, pMOB->GetMobDefinition() );


            if (pEffect)
                mMobDescriptor.SetState( pEffect->GetEffectState() );

            mMobDescriptors.Add( mMobDescriptor );
        }
    }

    return mMobDescriptors;
}


//================================================================
//Resourcec
//================================================================



    moResourceDescriptor moDirectorConsole::GetResourceDescriptor( moResourceDescriptor p_ResourceDescriptor ) {

        MOint result;
        moTexture* tex;

        if (!m_pResourceManager) {
            LogError(moText("Resource manager unavailable..."));
            return moResourceDescriptor();
        }

        switch( (int)p_ResourceDescriptor.GetResourceDefinition().GetType() ) {
            case MO_RESOURCETYPE_TEXTURE:

                //moTextureDescriptor TexDescriptor( );

                result = m_pResourceManager->GetTextureMan()->GetTextureMOId( p_ResourceDescriptor.GetResourceDefinition().GetName(), false );

                if (result!=-1) {
                    tex = m_pResourceManager->GetTextureMan()->GetTexture( result );
                    if (tex) {

                       	moText filename = m_pResourceManager->GetDataMan()->GetDataPath() + moSlash + (moText)tex->GetName();

                        if (tex->GetType()!=MO_TYPE_VIDEOBUFFER || tex->GetType()!=MO_TYPE_CIRCULARVIDEOBUFFER) {
                            if ( moFile( filename ).Exists() ) {
                                //filename is ok
                                if (tex->IsBuildedFromFile()) {
                                    //maybe a movie, lets doit
                                    //maybe is a movie or you cant loadit
                                    if ( tex->GetType()!=MO_TYPE_TEXTURE || p_ResourceDescriptor.IsCreateThumbnail() ) {
                                        //THEN CREATE THUMBNAIL
                                        //filename = tex->CreateThumbnail( "PNG", 132, 88 );
                                    }
                                }
                            } else {
                                //maybe is a movie or you cant loadit
                                //if ( p_ResourceDescriptor.IsCreateThumbnail() ) {
                                    //THEN CREATE THUMBNAIL
                                    //filename = tex->CreateThumbnail( moText("PNG"), 132, 88 );
                                //}
                            }
                        }

                        moTextureDescriptor pTextDesc( tex->GetName(),
                                                       filename,
                                                       0,
                                                       (moTextureType)tex->GetType(),
                                                       m_pResourceManager->GetDataMan()->GetDataPath() );



                       pTextDesc.SetSpecificParameters( tex->GetWidth(),
                                                        tex->GetHeight(),
                                                        tex->GetComponents(),
                                                        tex->GetMOId(),
                                                        tex->GetGLId(),
                                                        tex->GetTexParam(),
                                                        tex->IsBuildedFromFile() );


                        return pTextDesc;
                    }

                }
                break;
            case MO_RESOURCETYPE_SHADER:
                break;
        }

        return moResourceDescriptor(); // return MO_RESOURCETYPE_UNDEFINED
    }

    moResourceDescriptors moDirectorConsole::GetResourceDescriptors(  moResourceType p_ResourceType  ) {

        moResourceDescriptors   pResourceDescriptors;

        moTextureManager* pTM = NULL;

        switch( (int)p_ResourceType ) {
            case MO_RESOURCETYPE_TEXTURE:

                pTM = m_pResourceManager->GetTextureMan();

                if (pTM) {


                    moTexture*  tex;

                    for( MOuint i = 0; i< pTM->GetTextureCount(); i++) {

                        tex = pTM->GetTexture(i);
                        if (tex) {
                            //acá habría que diferenciar bien texturas pre-definidas de las cargadas por archivo...


                            moText filename = m_pResourceManager->GetDataMan()->GetDataPath() + moSlash + (moText)tex->GetName();
                            /*
                            if ( tex->GetType()!=MO_TYPE_TEXTURE ) {
                                //THEN CREATE THUMBNAIL
                                filename = tex->CreateThumbnail( moText("PNG"), 132, 88 );
                            }
                            */

                            moTextureDescriptor pTextDesc( tex->GetName(),
                                                           filename,
                                                           tex->GetWidth()*tex->GetHeight()*tex->GetComponents(), //just an idea of the size
                                                           (moTextureType)tex->GetType(),
                                                           m_pResourceManager->GetDataMan()->GetDataPath() );

                           pTextDesc.SetSpecificParameters( tex->GetWidth(),
                                                            tex->GetHeight(),
                                                            tex->GetComponents(),
                                                            tex->GetMOId(),
                                                            tex->GetGLId(),
                                                            tex->GetTexParam(),
                                                            tex->IsBuildedFromFile() );

                            pResourceDescriptors.Add( pTextDesc );

                            moResourceDescriptor testResourceDescriptor;

                            testResourceDescriptor = pResourceDescriptors[pResourceDescriptors.Count()-1];

                        }

                    }
                }

                break;

            case MO_RESOURCETYPE_FILTER:
                break;

            case MO_RESOURCETYPE_FONT:
                break;
        }

        return pResourceDescriptors;

    }


//================================================================
//MOB Moldeo Object
//================================================================

	moDirectorStatus
	moDirectorConsole::ImportMob( moText p_filename ) {

	    moConfig CheckConfig;
	    moMobDescriptor MobDescriptor;
        moProjectDescriptor ProjectDescriptor;
        moDirectorStatus	mStatus = MO_DIRECTOR_STATUS_ERROR;

        ProjectDescriptor = GetProject();
        int result;

	    result = CheckConfig.LoadConfig( p_filename );

	    if ( result == MO_CONFIG_OK ) {

	        //ShowMessage( p_filename + moText(" loaded") );

	        moText oname = CheckConfig.GetObjectName();
	        moText oclass = CheckConfig.GetObjectClass();
	        moFile fname(CheckConfig.GetName());
	        moText oconfigname = fname.GetFileName();
	        moMoldeoObjectType otype = moGetStrType( oclass );


	        Log( moText("importing:") + moText(" name:") + (moText)oname + moText(" class:") + (moText)oclass + moText(" confname:") + (moText)oconfigname );

            moMobDefinition MobDefinition;
            MobDefinition.SetName( oname );
            MobDefinition.SetConfigName( oconfigname );
            MobDefinition.SetType( otype );
            MobDefinition.SetLabelName( oconfigname );

            MobDescriptor.Set( ProjectDescriptor, MobDefinition );

            moText fullconfigname = m_pResourceManager->GetDataMan()->GetDataPath() + moSlash + MobDefinition.GetConfigName() + moText(".cfg");
            moFile destname(fullconfigname);

            //ShowMessage( fullconfigname + moText(" loaded") );

            if (!destname.Exists()) {
                if (moFileManager::CopyFile( p_filename, fullconfigname )) {
                    Log( fullconfigname + moText(" copied.") );
                }
            } else {
                ShowMessage( fullconfigname + moText(" exists already, just importing.") );
            }

            mStatus = NewMob( MobDescriptor );


        } else if ( result == MO_CONFIGFILE_NOT_FOUND ) {

            LogError( moText("Config filename ") + p_filename + moText(" not found ") );

            mStatus = MO_DIRECTOR_STATUS_NOT_FOUND;
        }

        return mStatus;
	}


	moDirectorStatus
	moDirectorConsole::OpenMob( moMobDescriptor p_MobDesc ) {

        //chequeamos que el config este cargado

        MOint verif;
        moMoldeoObject* pMOB;

		pMOB = GetObject( p_MobDesc );

        if (pMOB) {
            if (pMOB->GetConfig()) {
                if (pMOB->GetConfig()->IsConfigLoaded()) {

                    return this->EditMob( p_MobDesc );

                } else LogError("moDirectorConsole::OpenMob Config file isn't loaded.");
            } else LogError("moDirectorConsole::OpenMob Config object unavailable");
        } else LogError(moText("moDirectorConsole::OpenMob Object not founded. Name: ") +
                        moText(p_MobDesc.GetMobDefinition().GetName()) +
                        moText(" Config Name:") +
                        moText(p_MobDesc.GetMobDefinition().GetConfigName()) +
                        moText(" Type:") +
                        moText( p_MobDesc.GetMobDefinition().GetTypeStr() )
                        );

		// todo: try to reload config file...

		return MO_DIRECTOR_STATUS_ERROR;

	}

	moDirectorStatus
	moDirectorConsole::CloseMob( moMobDescriptor p_MobDesc ) {
		/*
		if ( 0<=p_MobDesc.GetIndex() && p_MobDesc.GetIndex()< m_ProjectDescriptor.GetMobsCount(p_MobDesc.GetType())) {

			if( m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].IsConfigLoaded() ) {
				m_pMobs[p_MobDesc.GetType()][p_MobDesc.GetIndex()].UnloadConfig();
				return MO_DIRECTOR_STATUS_OK;
			} else {
				return MO_DIRECTOR_STATUS_ERROR;
			}
		} else
		*/
		return MO_DIRECTOR_STATUS_ERROR;
	}

	moDirectorStatus
	moDirectorConsole::ReloadMob( moMobDescriptor p_MobDesc ) {
		return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moDirectorConsole::NewMob( moMobDescriptor p_MobDesc ) {

      m_timer.Stop();

      moText confignamecomplete = "";
      bool res = false;

	    p_MobDesc.SetProjectDescriptor( GetProject() );

	    moMobDefinition pMobDef = p_MobDesc.GetMobDefinition();

	    moEffect* pEffect = NULL;
	    moResource* pResource = NULL;
	    MOint rid = -1;
        moMoldeoObject* pMOB = NULL;

	    switch( (int) pMobDef.GetType()) {
	        case MO_OBJECT_PREEFFECT:
                pMobDef.SetConsoleParamIndex( m_Config.GetParamIndex("preeffect") );
                pMobDef.SetConsoleValueIndex( m_EffectManager.PreEffects().Count() );
                pMOB = (moMoldeoObject*)m_EffectManager.New( pMobDef );
                pEffect = (moEffect*) pMOB;
                if (pMOB) pMOB->GetConfig()->Set( pMOB->GetName(), "preeffect" );
                break;
            case MO_OBJECT_EFFECT:
                pMobDef.SetConsoleParamIndex( m_Config.GetParamIndex("effect") );
                pMobDef.SetConsoleValueIndex( m_EffectManager.Effects().Count() );
                pMOB = (moMoldeoObject*)m_EffectManager.New( pMobDef );
                pEffect = (moEffect*) pMOB;
                if (pMOB) pMOB->GetConfig()->Set( pMOB->GetName(), "effect" );
                break;
            case MO_OBJECT_POSTEFFECT:
                pMobDef.SetConsoleParamIndex( m_Config.GetParamIndex("posteffect") );
                pMobDef.SetConsoleValueIndex( m_EffectManager.PostEffects().Count() );
                pMOB = (moMoldeoObject*)m_EffectManager.New( pMobDef );
                pEffect = (moEffect*) pMOB;
                if (pMOB) pMOB->GetConfig()->Set( pMOB->GetName(), "posteffect" );
                break;
            case MO_OBJECT_MASTEREFFECT:
                pMobDef.SetConsoleParamIndex( m_Config.GetParamIndex("mastereffect") );
                pMobDef.SetConsoleValueIndex( m_EffectManager.MasterEffects().Count() );
                pMOB = (moMoldeoObject*)m_EffectManager.New( pMobDef );
                pEffect = (moEffect*) pMOB;
                if (pMOB) pMOB->GetConfig()->Set( pMOB->GetName(), "mastereffect" );
                break;
            case MO_OBJECT_IODEVICE:
                pMobDef.SetConsoleParamIndex( m_Config.GetParamIndex("devices") );
                pMobDef.SetConsoleValueIndex( m_pIODeviceManager->IODevices().Count() );
                pMOB = (moMoldeoObject*) m_pIODeviceManager->NewIODevice( pMobDef.GetName(), pMobDef.GetConfigName(), pMobDef.GetLabelName(), MO_OBJECT_IODEVICE, pMobDef.GetMobIndex().GetParamIndex(), pMobDef.GetMobIndex().GetValueIndex() );
                if (pMOB) pMOB->GetConfig()->Set( pMOB->GetName(), "iodevice" );
                break;
            case MO_OBJECT_RESOURCE:
                pMobDef.SetConsoleParamIndex( m_Config.GetParamIndex("resources") );
                pMobDef.SetConsoleValueIndex( m_Config.GetParam("resources").GetValuesCount() );
                rid = m_pResourceManager->GetResourceIndex( pMobDef.GetLabelName() );
                if(rid>-1) pResource = m_pResourceManager->GetResource(rid);

                if (pResource ) {
                    //do nothing
                    if (pResource->GetLabelName()!=pMobDef.GetLabelName()) {
                        pResource->SetConfigName( pMobDef.GetConfigName() );
                        pResource->SetLabelName( pMobDef.GetLabelName() );
                    } else LogError( moText("Resource already loaded: ") + (moText)pResource->GetLabelName() );
                } else
                if (m_pResourceManager->NewResource( pMobDef.GetName(), pMobDef.GetConfigName(), pMobDef.GetLabelName() )) {
                    rid = m_pResourceManager->GetResourceIndex( pMobDef.GetLabelName() );
                    if (rid>=0) {
                        pResource = m_pResourceManager->GetResource(rid);
                        if (pResource) {
                            pResource->SetConfigName( pMobDef.GetConfigName() );
                            pResource->SetLabelName( pMobDef.GetLabelName() );
                        }
                    }
                }
                pMOB = (moMoldeoObject*) pResource;

                pMOB->SetMobDefinition( pMobDef );

                if (pMOB) pMOB->GetConfig()->Set( pMOB->GetName(), "resource" );
                break;
            default:
                LogError(moText("NewMob: No mob type defined."));
                return MO_DIRECTOR_STATUS_ERROR;
                break;
        }

        if (pMOB) {

            if (pMOB->GetConfigName().Length()>0) {

                confignamecomplete = m_pResourceManager->GetDataMan()->GetDataPath();
                confignamecomplete +=  moSlash + moText(pMOB->GetConfigName());
                confignamecomplete +=  moText(".cfg");

                pMOB->GetDefinition();

                ///Creates the config file based on definition plugin
                moFile pFile(confignamecomplete);

                ///veamos si existe antes...
                if (!pFile.Exists()) {
                    ///si no existe lo creamos...
                    res = pMOB->GetConfig()->CreateDefault( confignamecomplete );

                } else {
                    ///si existe lo cargamos...
                    res = true;

                }

                if (res) {
                    pMOB->GetConfig()->UnloadConfig();

                    //inicializacion....
                    m_MoldeoObjects.Add( (moMoldeoObject*) pMOB );

                    pMOB->SetResourceManager( m_pResourceManager );

                    res = pMOB->Init();
                    if (res) {
                        if (pEffect) {
                            pEffect->LoadCodes( m_pIODeviceManager );
                            pEffect->Activate();
                        }
                    } else {
                        LogError( moText("moDirectorConsole::NewMob Couldn't initialized effect" ) );
                    }

                    //pEffect->Draw( &m_EffectState.tempo );
                    moValue effectvalue( pMOB->GetName(), "TXT" );
                    effectvalue.AddSubValue( pMOB->GetConfigName() , "TXT" );
                    effectvalue.AddSubValue( pMOB->GetLabelName() , "TXT" );
                    effectvalue.AddSubValue( "0" , "NUM" );
                    effectvalue.AddSubValue( "1" , "NUM" );

                    m_Config.GetParam( pMOB->GetMobDefinition().GetMobIndex().GetParamIndex() ).AddValue( effectvalue );

                    LoadConnections();
                    moMobDefinition MDef = pMOB->GetMobDefinition();
                    bool validity = MDef.IsValid();
                    if (validity==false) {
                      LogError( moText("NewMob:: Source > MobDefinition Invalid") );
                    } else ProjectUpdated( m_ProjectDescriptor );

                } else {
                    LogError( moText("moDirectorConsole::NewMob Couldn't create default configuration") );
                }

            } else {
                LogError( moText("moDirectorConsole::NewMob Config filename undefined" ) );
            }
        } else {
            LogError( moText("moDirectorConsole::NewMob Couldn't create effect: " ) + pMobDef.GetName() );
        }

        m_timer.Start(FRAME_MILIS);

        return MO_DIRECTOR_STATUS_ERROR;

	}


	moDirectorStatus moDirectorConsole::MoveMob( moMobDescriptor p_MobDesc, int position ) {

    ///chequea el objeto a mover

    moMoldeoObject* pObj = NULL;
    moMoldeoObject* pObjAux = NULL;
    int array_count = 0;
    moMoldeoObjectType MobType = p_MobDesc.GetMobDefinition().GetType();
    int index_object = p_MobDesc.GetMobDefinition().GetMobIndex().GetValueIndex();

    pObj = m_MoldeoObjects.GetRef(
                              RelativeToGeneralIndex( index_object, MobType )
                               );

    ///si el valor del indice nuevo es valido (esta en rango)
    switch( p_MobDesc.GetMobDefinition().GetType() ) {

      case MO_OBJECT_EFFECT:
        array_count = m_EffectManager.Effects().Count();
        break;
      case MO_OBJECT_PREEFFECT:
        array_count = m_EffectManager.PreEffects().Count();
        break;
      case MO_OBJECT_POSTEFFECT:
        array_count = m_EffectManager.PostEffects().Count();
        break;
      case MO_OBJECT_MASTEREFFECT:
        array_count = m_EffectManager.MasterEffects().Count();
        break;

      case MO_OBJECT_IODEVICE:
        array_count = m_pIODeviceManager->IODevices().Count();
        break;
      case MO_OBJECT_RESOURCE:
        //array_count = m_pResourceManager->Resources().Count();
        array_count = 0;
        LogError( "Sorry. Changing order of resources is not allowed yet." );
        return MO_DIRECTOR_STATUS_ERROR;
        break;
      default:
        array_count = 0;
        break;

    }


        if ( position >= 0 && position < array_count ) {

            ///hace un switch entre el objeto q estaba ahi y este...
            //p_MobDesc.GetMobDefinition().GetMobIndex().GetValueIndex()
            //moEffect* pObjFx = m_EffectManager.Effects().GetRef(index_object);
            int paramindex = p_MobDesc.GetMobDefinition().GetMobIndex().GetParamIndex();
            int valueindex = p_MobDesc.GetMobDefinition().GetMobIndex().GetValueIndex();

            int preconf1 = m_Config.GetValue( paramindex, valueindex ).GetSubValue(3).Int();
            int active1 = m_Config.GetValue( paramindex, valueindex ).GetSubValue(4).Int();

            ///intercambiamos los objetos dentro del array del effectmanager


            int diff = position - index_object;
            if (diff==0) {
              ///no se hace nada
            } else if (diff>0) {
              ///position es mas que index_object, el objeto baja en los indices

              /// se reordenan los objetos entre el position y el index_object....
              /// arrancando desde el index_object hasta el position
              for( int o = index_object; o < (position); o++ ) {

                ///intercambiamos los objetos... en el array
                pObjAux = m_MoldeoObjects.GetRef( RelativeToGeneralIndex( o+1, MobType ) );

                if ( MO_OBJECT_EFFECT<=MobType && MobType<=MO_OBJECT_PREEFFECT) m_EffectManager.Set( o, pObjAux );
                else if (MobType==MO_OBJECT_IODEVICE) m_pIODeviceManager->IODevices().Set( o, (moIODevice*)pObjAux );

                m_MoldeoObjects.Set( RelativeToGeneralIndex( o, MobType ) , pObjAux );

                ///intercambiamos los valores en el config y actualizamos los mobindex.... importante!!
                //moMobIndex mindex2 = pObjFxAux->GetMobDefinition().GetMobIndex();
                moMobIndex mindex2 = pObjAux->GetMobDefinition().GetMobIndex();
                int preconf2 = m_Config.GetValue( paramindex, mindex2.GetValueIndex() ).GetSubValue(3).Int();
                int active2 = m_Config.GetValue( paramindex, mindex2.GetValueIndex() ).GetSubValue(4).Int();

                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(0).SetText( pObjAux->GetName() );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(1).SetText( pObjAux->GetConfigName() );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(2).SetText( pObjAux->GetLabelName() );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(3).SetInt( preconf2 );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(4).SetInt( active2 );
                pObjAux->SetConsoleValueIndex( o );

              }
              ///al fin...
              if ( MO_OBJECT_EFFECT<=MobType && MobType<=MO_OBJECT_PREEFFECT) m_EffectManager.Set( position, pObj );
              else if (MobType==MO_OBJECT_IODEVICE) m_pIODeviceManager->IODevices().Set( position, (moIODevice*)pObj );

              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(0).SetText( pObj->GetName() );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(1).SetText( pObj->GetConfigName() );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(2).SetText( pObj->GetLabelName() );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(3).SetInt( preconf1 );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(4).SetInt( active1 );
              pObj->SetConsoleValueIndex( position );
              int mobsindx = RelativeToGeneralIndex( position, MobType );
              m_MoldeoObjects.Set( mobsindx, pObj );

            } else if (diff<0) {
              ///position es menos que index_object, el objeto sube en los indices

              /// se reordenan los objetos entre el position y el index_object....
              /// arrancando desde el position hasta el index_object
              for( int o = index_object ; o >= (position+1)  ; o-- ) {

               pObjAux = m_MoldeoObjects.GetRef( RelativeToGeneralIndex( o-1, MobType ) );

                if ( MO_OBJECT_EFFECT<=MobType && MobType<=MO_OBJECT_PREEFFECT) m_EffectManager.Set( o, pObjAux );
                else if (MobType==MO_OBJECT_IODEVICE) m_pIODeviceManager->IODevices().Set( o, (moIODevice*)pObjAux );

                m_MoldeoObjects.Set( RelativeToGeneralIndex( o, MobType ), pObjAux );

                moMobIndex mindex2 = pObjAux->GetMobDefinition().GetMobIndex();
                int preconf2 = m_Config.GetValue( paramindex, mindex2.GetValueIndex() ).GetSubValue(3).Int();
                int active2 = m_Config.GetValue( paramindex, mindex2.GetValueIndex() ).GetSubValue(4).Int();

                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(0).SetText( pObjAux->GetName() );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(1).SetText( pObjAux->GetConfigName() );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(2).SetText( pObjAux->GetLabelName() );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(3).SetInt( preconf2 );
                m_Config.GetParam( paramindex ).GetValue( o ).GetSubValue(4).SetInt( active2 );

                pObjAux->SetConsoleValueIndex( o );

              }
              ///al fin...
              if ( MO_OBJECT_EFFECT<=MobType && MobType<=MO_OBJECT_PREEFFECT) m_EffectManager.Set( position, pObj );
              else if (MobType==MO_OBJECT_IODEVICE) m_pIODeviceManager->IODevices().Set( position, (moIODevice*)pObj );

              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(0).SetText( pObj->GetName() );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(1).SetText( pObj->GetConfigName() );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(2).SetText( pObj->GetLabelName() );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(3).SetInt( preconf1 );
              m_Config.GetParam( paramindex ).GetValue( position ).GetSubValue(4).SetInt( active1 );
              pObj->SetConsoleValueIndex( position );
              int mobsindx = RelativeToGeneralIndex( position, MobType );
              m_MoldeoObjects.Set( mobsindx, pObj );
            }

        }

    LoadConnections();

    return ProjectUpdated( m_ProjectDescriptor );

    return MO_DIRECTOR_STATUS_ERROR;
	}

	moDirectorStatus moDirectorConsole::DuplicateMob( moMobDescriptor p_MobDesc ) {

    ///duplicar el archivo de configuracion agregandole un numero al final...
    moText datapath;
    moText filenameduplicate;
    moFile newfile;
    moText filename = p_MobDesc.GetMobDefinition().GetConfigName();
    moText labelname = p_MobDesc.GetMobDefinition().GetLabelName();
    moText labelnameduplicate;
    moDirectorStatus mStatus = MO_DIRECTOR_STATUS_ERROR;

    if (m_pResourceManager) {

      datapath = moMoldeoObject::m_pResourceManager->GetDataMan()->GetDataPath();

      filename = filename;
      labelname = labelname;

      filenameduplicate = filename + moText(".cfg");

      newfile.SetCompletePath( datapath + filenameduplicate );

      int count = 1;
      while( newfile.Exists() ) {
        filenameduplicate = filename + IntToStr( count );
        newfile.SetCompletePath( datapath + filenameduplicate + moText(".cfg") );
        count++;
      }

      m_pResourceManager->GetFileMan()->CopyFile( datapath + filename + moText(".cfg"), datapath + filenameduplicate + moText(".cfg")  );


      labelnameduplicate = labelname;

      ///modificar el labelname agregándole un número al final
      count = 1;
      while(LabelNameExists(labelnameduplicate)) {
        labelnameduplicate = labelname + IntToStr( count );
        count++;
      }

      ///importar este nuevo Mob...!!! que facil!!!
      p_MobDesc.GetMobDefinition().SetConfigName( filenameduplicate );
      p_MobDesc.GetMobDefinition().SetLabelName( labelnameduplicate );

      mStatus = NewMob( p_MobDesc );

    }

    return mStatus;
	}

	moDirectorStatus
	moDirectorConsole::EditMob( moMobDescriptor p_MobDesc ) {

        moDirectorStatus res;

        ///la orden de Edicion se manda al core: es un comando que implementa la interface
        /// crea el objeto correspondiente moDirectorFrameChild
        res = m_pDirectorCore->EditMob(p_MobDesc);

        if (res!=MO_DIRECTOR_STATUS_OK) {
            LogError( moText("moDirectorConsole::EditMob Couldn't edit ")+(moText)p_MobDesc.GetMobDefinition().GetConfigName());
            return MO_DIRECTOR_STATUS_ERROR;
        }

        ///ahora por cada parametro del objeto debemos notificar la interface para su edicion

        moMoldeoObject* pMOB = NULL;
        moConfig* pConfig = NULL;

        pMOB = GetObject( p_MobDesc );
        if (pMOB)
            pConfig = pMOB->GetConfig();
        else
            return MO_DIRECTOR_STATUS_ERROR;

        if (pConfig) {
            for( int i=0; i<pConfig->GetParamsCount(); i++ ) {

                moParam& Param( pConfig->GetParam(i));

                ///OJO!!! esto deberia estar en la inicializacion del config
                Param.GetParamDefinition().SetIndex(i);

                moParameterDescriptor ParamDescriptor( p_MobDesc, Param.GetParamDefinition(), i, Param.GetIndexValue() );

                /// notifica a la interface de la edicion del parametro
                this->EditParameter( ParamDescriptor );


                /// recorre los valores de este parámetro
                for( MOuint j=0; j<pConfig->GetParam(i).GetValuesCount(); j++) {

                    moValueIndex Vindex;

                    Vindex.m_ParamIndex = i;
                    Vindex.m_ValueIndex = j;

                    moValueDescriptor ValueDescriptor( ParamDescriptor, Vindex );
                    ValueDescriptor.SetValue(pConfig->GetParam(i).GetValue(j));

                    /// notifica a la interface de la edicion este valor
                    this->EditValue( ValueDescriptor );

                }

                //preconf ???
                ParameterUpdated( ParamDescriptor );

            }

            return MO_DIRECTOR_STATUS_OK;
        }

		return MO_DIRECTOR_STATUS_ERROR;
	}

	moDirectorStatus
	moDirectorConsole::SaveMob( moMobDescriptor p_MobDesc ) {

    moMoldeoObject* pMOB = NULL;

		MOint idx = p_MobDesc.GetMobDefinition().GetMobIndex().GetValueIndex();

		//if ( 0<=idx && idx < (int)m_EffectManager.Effects.Count() ) {
		//for ( int idx=0; idx < (int)m_MoldeoObjects.Count(); idx++ ) {
        switch( (int) p_MobDesc.GetMobDefinition().GetType() ) {
            case MO_OBJECT_PREEFFECT:
                pMOB = dynamic_cast<moMoldeoObject*>(m_EffectManager.PreEffects().GetRef(idx) );
                break;
            case MO_OBJECT_EFFECT:
                pMOB = dynamic_cast<moMoldeoObject*>(m_EffectManager.Effects().GetRef(idx));
                break;
            case MO_OBJECT_POSTEFFECT:
                pMOB = dynamic_cast<moMoldeoObject*>(m_EffectManager.PostEffects().GetRef(idx));
                break;
            case MO_OBJECT_MASTEREFFECT:
                pMOB = dynamic_cast<moMoldeoObject*>(m_EffectManager.MasterEffects().GetRef(idx));
                break;
            case MO_OBJECT_IODEVICE:
                pMOB = dynamic_cast<moMoldeoObject*>(m_pIODeviceManager->IODevices().GetRef(idx));
                break;
            case MO_OBJECT_RESOURCE:
                idx = m_pResourceManager->GetResourceIndex( p_MobDesc.GetMobDefinition().GetLabelName());
                if (idx!=-1)
                  pMOB = dynamic_cast<moMoldeoObject*>(m_pResourceManager->Resources().GetRef(idx));
                break;
        }

		if (!pMOB) {
		  LogError("Object not founded, maybe valueindex doesn't match. index =>"+IntToStr( idx ) );
		  return MO_DIRECTOR_STATUS_ERROR;
		}
		if (pMOB->GetConfig()->SaveConfig()!=MO_CONFIG_OK ) {
      return MO_DIRECTOR_STATUS_ERROR;
    } else return MO_DIRECTOR_STATUS_OK;
	}

	moDirectorStatus
	moDirectorConsole::DeleteMob( moMobDescriptor p_MobDesc ) {

    moMoldeoObject* pMOB;

    ///interrumpimos el timer (loop)
    m_timer.Stop();

		pMOB = GetObject( p_MobDesc );

		bool consoleinit = m_bInitialized;

        if (pMOB) {

            if ( pMOB->GetId() >= MO_MOLDEOOBJECTS_OFFSET_ID ) {

                //just wait until we delete the object
                //important to avoid conflicts on loop...
                //maybe MUST BE A LOCK
                m_bInitialized = false;


                MOint idx = p_MobDesc.GetMobDefinition().GetMobIndex().GetValueIndex();
                moMobIndex mobindex = p_MobDesc.GetMobDefinition().GetMobIndex();
                if (idx>-1) {
                    switch( (int)pMOB->GetType() ) {
                        case MO_OBJECT_PREEFFECT:
                        case MO_OBJECT_EFFECT:
                        case MO_OBJECT_POSTEFFECT:
                        case MO_OBJECT_MASTEREFFECT:
                            if (m_EffectManager.RemoveEffect( idx, pMOB->GetType())) {
                                ///remove from config
                                m_Config.GetParam( mobindex.GetParamIndex() ).DeleteValue( mobindex.GetValueIndex() );
                            }
                            break;
                        case MO_OBJECT_IODEVICE:
                            if ( m_pIODeviceManager ) {
                                m_pIODeviceManager->IODevices().Remove( idx );
                                ///remove from config
                                m_Config.GetParam( mobindex.GetParamIndex() ).DeleteValue( mobindex.GetValueIndex() );
                            }
                            break;
                        case MO_OBJECT_RESOURCE:
                            if (m_pResourceManager && m_pResourceManager->RemoveResource( idx ) ) {
                                ///remove from config
                                m_Config.GetParam( mobindex.GetParamIndex() ).DeleteValue( mobindex.GetValueIndex() );
                            }
                            break;
                    }
                }

                LoadConnections();

                ///back to previous state
                m_bInitialized = consoleinit;

                ///we've finished, update project
                ProjectUpdated( GetProject() );

                m_timer.Start( FRAME_MILIS );

            }
        }


		return MO_DIRECTOR_STATUS_OK;
	}

	moMobDescriptor
	moDirectorConsole::GetMob( moMobDescriptor p_MobDesc ) {

        moMoldeoObject* pMOB;

		pMOB = GetObject( p_MobDesc );

        if (pMOB) {
            /// TODO ya no deberia ser necesario pasar el puntero...esto se puede sacar

            switch(pMOB->GetType()) {
                case MO_OBJECT_IODEVICE:
                case MO_OBJECT_RESOURCE:
                case MO_OBJECT_CONSOLE:
                    p_MobDesc.SetState( pMOB->GetState() );
                    break;
                case MO_OBJECT_PREEFFECT:
                case MO_OBJECT_EFFECT:
                case MO_OBJECT_POSTEFFECT:
                case MO_OBJECT_MASTEREFFECT:
                    moEffect* pEffect = dynamic_cast<moEffect*>(pMOB);
                    if (pEffect) {
                      p_MobDesc.SetState( pEffect->GetEffectState() );
                    }
                    break;
            }

            return p_MobDesc;
        }

		return p_MobDesc; //sin modificaciones
	}

	moDirectorStatus
	moDirectorConsole::SetMob( moMobDescriptor p_MobDesc ) {

		moMoldeoObject* pMOB = GetObject( p_MobDesc );
		moEffect* Effect  = NULL;

        if (pMOB) {

            //wxMessageBox( moText2Wx( p_MobDesc.GetMobDefinition().GetLabelName() ) + IntToStr(p_MobDesc.GetEffectState().on) );
            switch(pMOB->GetType()) {

              case MO_OBJECT_PREEFFECT:
              case MO_OBJECT_EFFECT:
              case MO_OBJECT_POSTEFFECT:
              case MO_OBJECT_MASTEREFFECT:

                  Effect = dynamic_cast<moEffect*>( pMOB );

                  if (Effect) {

                    moEffectState fxstate = p_MobDesc.GetEffectState();
                    moEffectState old_fxstate = Effect->GetEffectState();

                    fxstate.CSV2RGB();

                    Effect->SetEffectState( fxstate );

                    if (fxstate.tempo.delta!=old_fxstate.tempo.delta) {
                       Effect->Unsynchronize();
                    }

                    /*
                    Effect->state.on = p_MobDesc.GetEffectState().on;
                    Effect->state.alpha = p_MobDesc.GetEffectState().alpha;
                    Effect->state.tint = p_MobDesc.GetEffectState().tint;
                    Effect->state.tintc = p_MobDesc.GetEffectState().tintc;
                    Effect->state.tints = p_MobDesc.GetEffectState().tints;
                    Effect->m_EffectState.tempo.delta = p_MobDesc.GetEffectState().tempo.delta;
                    Effect->state.synchronized= p_MobDesc.GetEffectState().synchronized;
                    */


                    /*
                    p_MobDesc.GetEffectState().tintr = Effect->state.tintr;
                    p_MobDesc.GetEffectState().tintg = Effect->state.tintg;
                    p_MobDesc.GetEffectState().tintb = Effect->state.tintb;
                    p_MobDesc.SetEffectState(Effect->GetEffectState());
                    */

                    //Effect->state = p_MobDesc.GetEffectState();

                    ///Traduce codigo en accion
                    switch( Effect->State()) {
                        case MO_TIMERSTATE_PAUSED:
                            Effect->Pause();
                            break;
                        case MO_TIMERSTATE_PLAYING:
                            if (Effect->State()==MO_TIMERSTATE_PAUSED) {
                                Effect->Play();
                            } else {
                                Effect->Continue();
                            }
                            break;
                        case MO_TIMERSTATE_STOPPED:
                            Effect->Stop();
                            break;
                    }


                    ///Una vez actualizado el efecto,
                    /// Devolvemos al Core el MobDescriptor con el ultimo estado del efecto (moEffectState).
                    p_MobDesc.SetEffectState( Effect->GetEffectState() );

                    /*
                    MODebug2->Push( "moDirectorConsole::SetMob sync: " + IntToStr((int)Effect->state.synchronized)
                                    +" tempo.on: " + IntToStr( (int)Effect->m_EffectState.tempo.Started() )
                                    +" tempo.pause_on: " + IntToStr( (int)Effect->m_EffectState.tempo.Paused())
                                    + " tempo.ticks: " + IntToStr( Effect->m_EffectState.tempo.ticks )
                                    + " tempo.ang: " + FloatToStr( Effect->m_EffectState.tempo.ang ) );
                    */

                    MobUpdated( p_MobDesc );
                  }
                  break;
              case MO_OBJECT_CONSOLE:

                break;

            }

            return MO_DIRECTOR_STATUS_OK;
        }

		return MO_DIRECTOR_STATUS_ERROR;
	}


	moParameterDescriptors  moDirectorConsole::GetParameterDescriptors( moMobDescriptor p_MobDesc) {

        moParameterDescriptors    mParameterDescriptors;
        moMoldeoObject* pMOB = GetObject( p_MobDesc );

        if (pMOB) {

            moConfig* pConfig = pMOB->GetConfig();

            if ( pConfig ) {
                if (pConfig->IsConfigLoaded() ) {
                    for(int i=0; i < pConfig->GetParamsCount(); i++) {

                        moParam& mParam( pConfig->GetParam(i) );

                        moParamDefinition mParamDefinition( mParam.GetParamDefinition() );
                        moParameterDescriptor   mParamDescriptor( p_MobDesc, mParamDefinition, i, mParam.GetIndexValue() );

                        mParameterDescriptors.Add( mParamDescriptor );
                    }
                }
            }

        }

	    return mParameterDescriptors;
    }


moDirectorStatus
moDirectorConsole::SetParameter( moParameterDescriptor  p_ParameterDesc ) {

    moMoldeoObject* pMOB = GetObject( p_ParameterDesc.GetMobDescriptor() );
    if (pMOB) {

        moConfig* pConfig = NULL;

        pConfig = pMOB->GetConfig();
        if (pConfig) {
            moParam& Param( pConfig->GetParam( p_ParameterDesc.GetIndex() ) );

            Param.SetIndexValue( p_ParameterDesc.GetIndexValue() );

            ParameterUpdated( p_ParameterDesc );

            return MO_DIRECTOR_STATUS_OK;
        }

    }
    return MO_DIRECTOR_STATUS_ERROR;
}

//=========================================================================================================================
//
//=========================================================================================================================

    moValueDescriptor moDirectorConsole::GetValue( moValueDescriptor p_ValueDesc ) {

        moConfig* pConfig;
        moMoldeoObject* pObject;


        pObject = GetObject( p_ValueDesc.GetParamDescriptor().GetMobDescriptor() );
        if (pObject) {

             pConfig = pObject->GetConfig();

            if (pConfig) {

                moParamDefinition ParamDef = p_ValueDesc.GetParamDescriptor().GetParamDefinition();

                moParam& Param( pConfig->GetParam( ParamDef.GetIndex() ) );

                moValue& Value( Param.GetValue( p_ValueDesc.GetValueIndex().m_ValueIndex ) );

                p_ValueDesc.SetValue( Value );
            }
        }

        return p_ValueDesc;
    }

	moDirectorStatus moDirectorConsole::InsertValue( moValueDescriptor p_ValueDesc ) {

        //insert value...
        //at the end...
        moConfig* pConfig;
        moMoldeoObject* pObject;


        pObject = GetObject( p_ValueDesc.GetParamDescriptor().GetMobDescriptor() );
        pConfig = pObject->GetConfig();

        moParam& Param( pConfig->GetParam( p_ValueDesc.GetParamDescriptor().GetIndex() ) );

        Param.AddValue( p_ValueDesc.GetValue() );

        int newindexvalue = Param.GetValuesCount() - 1;

        p_ValueDesc.GetValueDefinition().SetIndex( newindexvalue );
        p_ValueDesc.GetValueIndex().m_ValueIndex =  newindexvalue;

        EditValue( p_ValueDesc );

        p_ValueDesc.GetParamDescriptor().SetIndexValue(newindexvalue);

        Param.SetIndexValue( newindexvalue );
        ParameterUpdated( p_ValueDesc.GetParamDescriptor() );

	    return MO_DIRECTOR_STATUS_OK;
    }

    moDirectorStatus moDirectorConsole::DeleteValue( moValueDescriptor p_ValueDesc ) {

        moConfig* pConfig;
        moMoldeoObject* pObject;


        pObject = GetObject( p_ValueDesc.GetParamDescriptor().GetMobDescriptor() );
        pConfig = pObject->GetConfig();

        moParam& Param( pConfig->GetParam( p_ValueDesc.GetParamDescriptor().GetIndex() ) );

        if ( Param.GetValuesCount() > 1 ) {
            Param.DeleteValue( p_ValueDesc.GetValueIndex().m_ValueIndex );
        } else return MO_DIRECTOR_STATUS_ERROR;

        return MO_DIRECTOR_STATUS_OK;
    }

	moDirectorStatus moDirectorConsole::SaveValue( moValueDescriptor p_ValueDesc ) {

        //save value in config class


	    return MO_DIRECTOR_STATUS_OK;
    }

    moDirectorStatus moDirectorConsole::SetValue( moValueDescriptor p_ValueDesc ) {

        ///aqui hay q tratar correctamente los errores...

        int idx;
        moFont* pFont;
        moText tt;

        ///fija el valor dentro del config y chequea de actualizar el MOB
        moConfig* pConfig;
        moMoldeoObject* pObject;


        mo3dModel* pModel;
        mo3DModelSceneNode* p3DModel;

        bool firsthaschange = false;
        bool secondhaschange = false;
        bool thirdhaschange = false;


        pObject = GetObject( p_ValueDesc.GetParamDescriptor().GetMobDescriptor() );
        if (pObject) {
            pConfig = pObject->GetConfig();

            if (pConfig) {
                moParamDefinition ParamDef = p_ValueDesc.GetParamDescriptor().GetParamDefinition();
                moParam& Param( pConfig->GetParam( ParamDef.GetIndex() ) );
                moValue& Value( Param.GetValue( p_ValueDesc.GetValueIndex().m_ValueIndex ) );
                moValue& NewValue(p_ValueDesc.GetValue());


                ///=============================================
                ///COMPARAMOS CON EL ANTERIOR (JUST FOR SHADERS)
                ///=============================================

                firsthaschange = !( Value.GetSubValue(0).Text() == NewValue.GetSubValue(0).Text() ) ||
                                  ( NewValue.GetSubValueCount()!=Value.GetSubValueCount() );

                ///generalmente deberia ser de minimo 4 subvalores
                if ( NewValue.GetSubValueCount() > 1 ) {
                    if ( NewValue.GetSubValueCount() > Value.GetSubValueCount() && NewValue.GetSubValue(1).Text()!=moText("") ) {
                        secondhaschange = true;
                    } else {
                        secondhaschange = !( Value.GetSubValue(1).Text() == NewValue.GetSubValue(1).Text() );
                    }
                }
                if ( NewValue.GetSubValueCount() > 2 ) {
                    if ( NewValue.GetSubValueCount() > Value.GetSubValueCount() && NewValue.GetSubValue(2).Text()!=moText("") ) {
                        thirdhaschange =  true;
                    } else {
                        thirdhaschange = !( Value.GetSubValue(2).Text() == NewValue.GetSubValue(2).Text() );
                    }
                }



                ///ahora segun el tipo de parametro se procesa el valor...
                switch(ParamDef.GetType()) {
                    case MO_PARAM_ALPHA:
                    case MO_PARAM_FUNCTION:
                    case MO_PARAM_TRANSLATEX:
                    case MO_PARAM_TRANSLATEY:
                    case MO_PARAM_TRANSLATEZ:
                    case MO_PARAM_SCALEX:
                    case MO_PARAM_SCALEY:
                    case MO_PARAM_SCALEZ:
                    case MO_PARAM_ROTATEX:
                    case MO_PARAM_ROTATEY:
                    case MO_PARAM_ROTATEZ:
                    case MO_PARAM_SYNC:
                    case MO_PARAM_PHASE:
                        ///asigna el nuevo valor al config

                        idx = m_pResourceManager->GetMathMan()->AddFunction( NewValue.GetSubValue(0).Text(), (MOboolean)false, pObject );

                        ///si no puede asignar la función no hace mas nada
                        if (idx>-1) {
                            NewValue.GetSubValue(0).SetFun( m_pResourceManager->GetMathMan()->GetFunction(idx) );
                            Value = NewValue;
                            ///el problema es que se pierde el foco
                        } else return MO_DIRECTOR_STATUS_ERROR;
                        break;

                    case MO_PARAM_NUMERIC:
                        /*char* vtext = (char*)p_ValueDesc.GetValue().GetSubValue().Text();
                        MOlong ivalue = strtol( "%i", &vtext, 10 );
                        Value.GetSubValue(0).SetInt( ivalue );
                        */
                        //asigna el nuevo valor al config
                        Value = NewValue;
                        break;

                    case MO_PARAM_TEXT:

                        ///directo, no chequeamos errores aqui, no sabríamos que chequear... cadena invalida?

                        Value = NewValue;
                        tt = moText("texto:") + Value.GetSubValue(0).Text();
                        MODebug2->Push( tt );
                        break;
                    case MO_PARAM_3DMODEL:
                    case MO_PARAM_OBJECT:

                        pModel = m_pResourceManager->GetModelMan()->Get3dModel( NewValue.GetSubValue(0).Text() );
                        p3DModel = new mo3DModelSceneNode();
                        if (p3DModel) p3DModel->Init(pModel);

                        ///igualmente, si el modelo es nulo entonces no hay modelo
                        if (pModel) {
                            NewValue.GetSubValue(0).SetModel( (mo3DModelSceneNode*)pModel );
                            Value = NewValue;
                        } else return MO_DIRECTOR_STATUS_ERROR;
                        break;

                    case MO_PARAM_FONT:
                        ///la fuente necesita 3 parámetros
                        if ( NewValue.GetSubValueCount() == 3 ) {
                            pFont = m_pResourceManager->GetFontMan()->GetFont( NewValue, true );
                            ///la fuente es creada o existe
                            if (pFont) {
                                ///asignamos el puntero de la fuente al valor
                                NewValue.GetSubValue(0).SetFont( pFont );
                                //Value.GetSubValue(2).SetInt();

                                ///correcto: asignamos el valor
                                Value = NewValue;
                            } else return MO_DIRECTOR_STATUS_ERROR;
                        } else return MO_DIRECTOR_STATUS_ERROR;
                        break;

                    case MO_PARAM_TEXTURE:
                    case MO_PARAM_VIDEO:
                        /// TODO: reescribir teniendo en cuenta si tiene o no aplicado un shader...
                        if ( Param.GetParamDefinition().GetType() == MO_PARAM_TEXTURE
                            || Param.GetParamDefinition().GetType() == MO_PARAM_VIDEO ) {

                            moValueBase& valuebase( Value.GetSubValue(0) );

                            ///=========================================
                            /// PRIMER SUBVALOR CORRESPONDE AL ARCHIVO DE LA IMAGEN
                            /// SI CAMBIA DEBEMOS RECARGARLO TODO
                            ///=========================================
                            if ( firsthaschange ) {

                                idx = m_pResourceManager->GetTextureMan()->GetTextureMOId( NewValue.GetSubValue(0).Text(), true);

                                ///si la textura nueva se cargo
                                if (idx>-1) {
                                    ///asignamos el puntero
                                    moTexture*  pTexture = m_pResourceManager->GetTextureMan()->GetTexture(idx);
                                    ///copiamos los valores de texto correspondientes
                                    valuebase = NewValue.GetSubValue(0);
                                    valuebase.SetTexture( pTexture );

                                    if ( NewValue.GetSubValueCount()==1 )
                                      Value.RemoveSubValues(true);///asegurarnos que solo hay un subvalor

                                    Log( moText("moDirectorConsole::SetValue() Assigned new texture ") + Param.GetParamDefinition().GetName() );
                                } else {
                                    LogError( moText("Param ") + Param.GetParamDefinition().GetName() +  moText(" Texture undefined") );
                                    return MO_DIRECTOR_STATUS_ERROR;
                                }

                            }

                            ///=====================================================================
                            /// SI ELSEGUNDO CAMBIO CORRESPONDE AL NOMBRE DEL CONFIG DEL SHADER
                            /// SI firsthaschange ESTE PASO ES OBLIGATORIO
                            ///=====================================================================
                            if  ( NewValue.GetSubValueCount()>1 ) {

                                if ( firsthaschange || secondhaschange || thirdhaschange ) {
                                    ///============================
                                    /// RECARGAMOS EL TEXTUREFILTER
                                    ///============================
                                    idx = m_pResourceManager->GetShaderMan()->GetTextureFilterIndex()->TextureFilterExists( &NewValue );

                                    ///si el texturefilter no existe...
                                    if (idx==-1) {
                                        ///entonces tratamos de cargarlo
                                        idx = m_pResourceManager->GetShaderMan()->GetTextureFilterIndex()->LoadFilter( &NewValue );

                                        /// el idx devuelve el n-eavo filtro creado
                                        /// si se agrego correctamente al TextureFilterIndex del ShaderManager
                                        if ( (idx-1)>=0 && (idx-1) < m_pResourceManager->GetShaderMan()->GetTextureFilterIndex()->Count() ) {

                                            ///entonces lo pedimos para asignarlo a nuestro valor base...
                                            moTextureFilter*  pTextureFilter = m_pResourceManager->GetShaderMan()->GetTextureFilterIndex()->Get(idx-1);
                                            valuebase.SetTextureFilter( pTextureFilter );

                                            if (Value.GetSubValueCount()>=2) Value.GetSubValue(1) = NewValue.GetSubValue(1);
                                            else Value.AddSubValue( NewValue.GetSubValue(1) );

                                            if (Value.GetSubValueCount()>=3) Value.GetSubValue(2) = NewValue.GetSubValue(2);
                                            else Value.AddSubValue( NewValue.GetSubValue(2) );

                                            Log( moText("moDirectorConsole::SetValue() New filter loaded and assigned "));

                                        } else {
                                            LogError( moText("Param ") + Param.GetParamDefinition().GetName() +  moText(" Texture filter undefined") );
                                            return MO_DIRECTOR_STATUS_ERROR;
                                        }
                                    } else {
                                        moText tfname = m_pResourceManager->GetShaderMan()->GetTextureFilterIndex()->MakeTextureFilterLabelName( &NewValue );
                                        LogError( moText("moDirectorConsole::SetValue() Warning Param ") + Param.GetParamDefinition().GetName() +  moText(" Texture filter already defined: ") + (moText)tfname );

                                        ///textura de filtro ya definida!!!
                                        ///por las dudas volvemos a asignar el puntero y sus valores de config(subvalor 1) y textura de destino (subvalor 2)
                                        moTextureFilter*  pTextureFilter = m_pResourceManager->GetShaderMan()->GetTextureFilterIndex()->Get(idx);
                                        valuebase.SetTextureFilter( pTextureFilter );
                                        if (Value.GetSubValueCount()>=2) Value.GetSubValue(1) = NewValue.GetSubValue(1);
                                        else Value.AddSubValue( NewValue.GetSubValue(1) );
                                        if (Value.GetSubValueCount()>=3) Value.GetSubValue(2) = NewValue.GetSubValue(2);
                                        else Value.AddSubValue( NewValue.GetSubValue(2) );
                                        return MO_DIRECTOR_STATUS_ERROR;
                                    }


                                }
                            }

                            ///====================================================================
                            /// AHORA TRATEMOS DE AJUSTAR EL ALFA DE FILTRO SI EL PARAMETRO EXISTE
                            ///====================================================================

                            if (NewValue.GetSubValueCount()>=4) {

                                ///======================================
                                ///         ALPHA FILTER
                                ///======================================

                                ///es el subvalor 3 (4to)

                                moValueBase& VAlpha( NewValue.GetSubValue(3) );

                                ///deberia tratarse de una función (el dato siempre es un texto en su primera etapa)
                                if ( VAlpha.GetType()==MO_VALUE_FUNCTION ) {

                                    ///creamos la funcion
                                    idx = m_pResourceManager->GetMathMan()->AddFunction( VAlpha.Text(), (MOboolean)false, pObject );

                                    ///si se creo
                                    if (idx>-1) {
                                        ///la asignamos
                                        VAlpha.SetFun( m_pResourceManager->GetMathMan()->GetFunction(idx) );

                                        ///ATENCION!!!: en moValue::SetTextureFilterAlpha evaluamos en  (T = 0) !!!!
                                        ///la funcion no se evalua!

                                        ///asignamos al valuebase de Value, o sea el subvalor 0
                                        valuebase.SetTextureFilterAlpha( VAlpha.GetData() );

                                        ///actualizamos o creamos el 4to valor....
                                        if (Value.GetSubValueCount()>=4) Value.GetSubValue(3) = NewValue.GetSubValue(3);
                                        else Value.AddSubValue( NewValue.GetSubValue(3) );
                                    } else return MO_DIRECTOR_STATUS_ERROR;

                                }


                            }


                            ///======================================
                            ///     PARAMETROS DE FILTRO:
                            ///     aqui seguirian todos los parametros complementarios al filtro
                            ///     a implementar y probar
                            ///
                            ///
                            ///======================================

                            /*
                            if (NewValue.GetSubValueCount()>4) {
                                //tenemos que usar los filtros-param
                                moTextFilterParam*  pFilterParam = new moTextFilterParam();

                                for( int i=4; i<(int)NewValue.GetSubValueCount(); i++) {
                                    //si o si tenemos que usar los codes... o names para los subvalores...
                                    moValueBase& vbase( NewValue.GetSubValue(i) );

                                    if ( vbase.GetCodeName() == moText("float1") ) {
                                        if ( vbase.Type() == MO_DATA_NUMBER_FLOAT ) {
                                            pFilterParam->par_flt1 = vbase.Float();
                                        }
                                    } else
                                    if ( vbase.GetCodeName() == moText("float2") ) {
                                        if ( vbase.Type() == MO_DATA_NUMBER_FLOAT ) {
                                            pFilterParam->par_flt2 = vbase.Float();
                                        }
                                    } else
                                    if ( vbase.GetCodeName() == moText("float3") ) {
                                        if ( vbase.Type() == MO_DATA_NUMBER_FLOAT ) {
                                            pFilterParam->par_flt3 = vbase.Float();
                                        }
                                    } else
                                    if ( vbase.GetCodeName() == moText("mat2") ) {
                                        if ( vbase.Type() == MO_DATA_VECTOR && vbase.Size() == 4 ) {
                                            float* vector = (float*)vbase.Pointer();
                                            for( int i=0; i<4 , pFilterParam->par_mat2[i] = vector[i] ; i++);
                                        }
                                    } else
                                    if ( vbase.GetCodeName() == moText("mat3") ) {
                                        if ( vbase.Type() == MO_DATA_VECTOR && vbase.Size() == 9 ) {
                                            float* vector = (float*)vbase.Pointer();
                                            for( int i=0; i<9 , pFilterParam->par_mat3[i] = vector[i] ; i++);
                                        }
                                    } else
                                    if ( vbase.GetCodeName() == moText("mat4") ) {
                                        if ( vbase.Type() == MO_DATA_VECTOR && vbase.Size() == 16 ) {
                                            float* vector = (float*)vbase.Pointer();
                                            for( int i=0; i<16 , pFilterParam->par_mat4[i] = vector[i] ; i++);
                                        }
                                    }
                                }
                                Value.GetSubValue(0).SetTextureFilterParam( pFilterParam );
                            }
                            */

                            //NewValue.GetSubValue(0) = Value.GetSubValue(0);
                            //Value.GetSubValue(0) = ;
                            //Value = NewValue;
                        }
                        break;
                    case MO_PARAM_SOUND:
                      if ( Param.GetParamDefinition().GetType() == MO_PARAM_SOUND ) {

                            if ( NewValue.GetSubValue(0).Text()!=Value.GetSubValue(0).Text() ) {

                              ///referenciamos el valor actual del config para modificarlo
                              moValueBase& valuebase( Value.GetSubValue(0) );

                              moSound* pSound = m_pResourceManager->GetSoundMan()->GetSound( NewValue.GetSubValue(0).Text() );
                              if (pSound) {
                                valuebase.SetText(NewValue.GetSubValue(0).Text());
                                valuebase.SetSound( pSound );
                                Log( moText("moDirectorConsole::SetValue() Assigned new sound.") + Param.GetParamDefinition().GetName() + " Sound: " + valuebase.Text() );
                              } else {
                                LogError( moText("moDirectorConsole::SetValue() Couldn't found or create new sound: ") + valuebase.Text() );
                              }

                            }
                      }
                      break;
                    case MO_PARAM_FILTER:
                        ///A implementar...
                        //Value.GetSubValue(0).SetText(  );
                        //Value = NewValue;
                        break;

                    case MO_PARAM_BLENDING:
                        ///Sin mayores inconvenientes, deberíamos probar q el entero está dentro del rango
                        if ( 0<=NewValue.GetSubValue(0).Int() && NewValue.GetSubValue(0).Int()< MO_BLENDINGS) {
                          Value = NewValue;
                        } else {
                            LogError( moText("Blending fuera de rango") );
                        }
                        break;
                    case MO_PARAM_POLYGONMODE:
                        ///Sin mayores inconvenientes, deberíamos probar q el entero está dentro del rango
                        if ( 0<=NewValue.GetSubValue(0).Int() && NewValue.GetSubValue(0).Int()< MO_POLYGONMODES) {
                          Value = NewValue;
                        } else {
                            LogError( moText("PolygonMode fuera de rango") );
                        }
                        break;

                    case MO_PARAM_COLOR:
                        ///RED=============================================================================
                        if ( Value.GetSubValue(MO_RED).Text()!=NewValue.GetSubValue(MO_RED).Text() ) {
                          idx = m_pResourceManager->GetMathMan()->AddFunction( NewValue.GetSubValue(MO_RED).Text(), (MOboolean)false, pObject );
                          if (idx>-1) {
                              Value.GetSubValue(MO_RED).SetText( NewValue.GetSubValue(MO_RED).Text() );
                              Value.GetSubValue(MO_RED).SetFun( m_pResourceManager->GetMathMan()->GetFunction(idx) );
                          } else return MO_DIRECTOR_STATUS_ERROR;
                        }
                        ///GREEN=============================================================================
                        if ( Value.GetSubValue(MO_GREEN).Text()!=NewValue.GetSubValue(MO_GREEN).Text() ) {
                          idx = m_pResourceManager->GetMathMan()->AddFunction( NewValue.GetSubValue(MO_GREEN).Text(), (MOboolean)false, pObject );
                          if (idx>-1) {
                              Value.GetSubValue(MO_GREEN).SetText( NewValue.GetSubValue(MO_GREEN).Text() );
                              Value.GetSubValue(MO_GREEN).SetFun( m_pResourceManager->GetMathMan()->GetFunction(idx) );
                          } else return MO_DIRECTOR_STATUS_ERROR;
                        }
                        ///BLUE=============================================================================
                        if ( Value.GetSubValue(MO_BLUE).Text()!=NewValue.GetSubValue(MO_BLUE).Text() ) {
                          idx = m_pResourceManager->GetMathMan()->AddFunction( NewValue.GetSubValue(MO_BLUE).Text(), (MOboolean)false, pObject );
                          if (idx>-1) {
                              Value.GetSubValue(MO_BLUE).SetText( NewValue.GetSubValue(MO_BLUE).Text() );
                              Value.GetSubValue(MO_BLUE).SetFun( m_pResourceManager->GetMathMan()->GetFunction(idx) );
                          } else return MO_DIRECTOR_STATUS_ERROR;
                        }
                        ///ALPHA=============================================================================
                        if ( Value.GetSubValue(MO_ALPHA).Text()!=NewValue.GetSubValue(MO_ALPHA).Text() ) {
                          idx = m_pResourceManager->GetMathMan()->AddFunction( NewValue.GetSubValue(MO_ALPHA).Text(), (MOboolean)false, pObject );
                          if (idx>-1) {
                              Value.GetSubValue(MO_ALPHA).SetText( NewValue.GetSubValue(MO_ALPHA).Text() );
                              Value.GetSubValue(MO_ALPHA).SetFun( m_pResourceManager->GetMathMan()->GetFunction(idx) );
                          } else return MO_DIRECTOR_STATUS_ERROR;
                        }
                        break;

                    case MO_PARAM_SCRIPT:
                        ///al pasar el valor de texto "__compiling__.lua"
                        if ( NewValue.GetSubValue(0).Text() == moText("__compiling__.lua") ) {
                            ///la consola interpreta que debe tomar el script del valor ya existente y compilarlo

                            ///tomamos el nombre completo del script
                            moText fullscript = m_pResourceManager->GetDataMan()->GetDataPath()+ moSlash + (moText)Value.GetSubValue(0).Text();

                            ///le pedimos al Moldeo Object que lo compile
                            if ( pObject->CompileFile(fullscript) ) {

                                MODebug2->Message(moText("ParticlesSimple script compiled succesfully ") + (moText)fullscript );

                                ///todo funciono de maravilla, ahora le damos Init otra vez
                                pObject->SelectScriptFunction( "Init" );
                                //AddFunctionParam( m_FramesPerSecond );
                                pObject->RunSelectedFunction();

                            } else MODebug2->Error(moText("ParticlesSimple couldnt compile lua script ") + (moText)fullscript );
                        } else {
                            ///aquí quizás estemos asignando simplemente un nuevo script.
                            if ( Value.GetSubValue(0).Text() != NewValue.GetSubValue(0).Text() ) {
                                ///tenemos una nueva cadena, chequeamos si existe como archivo
                                ///OJO: en caso de cambiar, deberiamos eliminar el script anterior....
                                ///TODO: completar esto!!!!
                                Value = NewValue;
                            }
                        }
                        break;

                    default:
                        ///si no sabemos de que valor se trata
                        ///probablemente sea de tipo NUMERIC en sus versiones de float, entero o long
                        Value = NewValue;
                        break;
                };

                ///para aquellos datos que implican cambios, lo fijamos de nuevo...
                    // funciones, colores, texturas filtradas, objetos, fuentes, etc...
                p_ValueDesc.SetValue( Value );

                ///notificamos todos los modulos de la actualizacion de estos datos
                ///esto es importante para actualizar los campos dentro de la interface
                ValueUpdated( p_ValueDesc );
            } //fin config
        } //fin object

	    return MO_DIRECTOR_STATUS_OK;
    }


moValueDescriptors  moDirectorConsole::GetValueDescriptors( moParameterDescriptor p_ParamDesc ) {

    moValueDescriptors mValues;

    moConfig* pConfig;
    moMoldeoObject* pObject;


    pObject = GetObject( p_ParamDesc.GetMobDescriptor() );
    if (pObject) {

        pConfig = pObject->GetConfig();

        if (pConfig) {

            moParamDefinition ParamDef = p_ParamDesc.GetParamDefinition();

            moParam& Param( pConfig->GetParam( ParamDef.GetIndex() ) );

            for( int i=0; i< (int)Param.GetValuesCount(); i++ ) {

                //moValue& Value( Param.GetValue( i ) );

                moValueIndex ix;
                ix.m_ParamIndex = Param.GetParamDefinition().GetIndex();
                ix.m_ValueIndex = i;

                mValues.Add( moValueDescriptor(  p_ParamDesc, ix ) );

            }
        }
    }


    return mValues;
}


void
moDirectorConsole::OnTimer( wxTimerEvent &event) {

	m_timerticks = moGetTicks();
	ConsoleLoop();

}


void
moDirectorConsole::Draw() { //refresh actual console.cfg file with their effects.cfg


	if( Initialized() ) {
		moConsole::Draw();
	}


}

MOulong
moDirectorConsole::GetTicks() {

	return m_timerticks;

}

/**
*
*   Override moConsole::GLSwapBuffers()
*
*/

void
moDirectorConsole::GLSwapBuffers() {


    if (m_pDirectorCore)
        m_pDirectorCore->ViewSwapBuffers();


}


void
moDirectorConsole::GUIYield() {

  wxTheApp->Yield();

}

moDirectorStatus
moDirectorConsole::SetView( int x, int y, int w, int h ) {

    Log( moText("moDirectorConsole::SetView Changing View: ") + IntToStr(w) + moText("X") + IntToStr(h) );

    if (Initialized()) {
        Log( moText("moDirectorConsole::SetView WITH CONSOLE") );
        if (m_pResourceManager) {
            if (m_pResourceManager->Initialized()) {
                if (m_pResourceManager->GetRenderMan()) {
                  m_pResourceManager->GetRenderMan()->Finish();
                  m_pResourceManager->GetRenderMan()->Init( RENDERMANAGER_MODE_NORMAL, w, h, w, h);
                  Log( moText("moDirectorConsole::SetView Render Manager Resized > ") + IntToStr(w) + moText("X") + IntToStr(h) );
                }

            }
        }
    } else {
        Log( moText("moDirectorConsole::SetView NO CONSOLE YET > size:") + IntToStr(w) + moText("X") + IntToStr(h)  );

        glViewport( 0, 0, w, h );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        double ratio =(double) w /(double) h;
        gluPerspective( 60.0,ratio, 0.0, 1024.0 );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

    }

    return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus moDirectorConsole::Play() {

    ConsolePlay();

    return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus moDirectorConsole::Pause() {

    ConsolePause();

    return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus moDirectorConsole::Stop() {

    ConsoleStop();

    return MO_DIRECTOR_STATUS_OK;
}

moDirectorStatus moDirectorConsole::Seek( MOulong p_timecode ) {

    moSetDuration( p_timecode );

    return MO_DIRECTOR_STATUS_OK;
}


moDirectorStatus moDirectorConsole::SaveSession() {
    ///return m_pDirectorConsole->SaveSession();

    /**/

    moDataSession* pDataSession = m_pResourceManager->GetDataMan()->GetSession();


    /*pDataSession->Set(   moText("NAME"),
            moDataSessionConfig* pSessionConfig,
            moDataSessionMode p_sessionmode,
            moDataSessionRecordMode p_recordmode,
            moDataSessionPlaybackMode p_playbackmode )
*/

    if (pDataSession) pDataSession->RecordLive( m_pResourceManager );



    return MO_DIRECTOR_STATUS_OK;
}



moDirectorStatus moDirectorConsole::ConsoleLoop() {

    if ( moAbstract::Initialized()) {
        Interaction();
        Update();
        Draw();
        //Errores::: basado en moDebug, o moTextHeap
        moText plog;
        for(int i =0; i < MODebug2->Count(); i++ ) {
            plog = MODebug2->Pop();
            wxString mess;
            mess = moText2Wx( plog );
            bool iserror;
            iserror = ( mess.Find(wxString(_("ERROR"))) >= 0 );
            if (iserror) {
                if (plog.Trim()!=moText("")) LogError( plog );
            } else {
                if (plog.Trim()!=moText("")) Log( plog );
            }
        }

        if (previewreset2 && ( moGetTicks() / 1000) > 2 ) {
            m_pDirectorCore->ProjectPreview();
            //wxMessageBox("preview reset 2");
            moStopTimer();
            moStartTimer();
            previewreset2 = false;
        }
		if ( previewreset && ( moGetTicks() / 1000) > 1) {
            m_pDirectorCore->ProjectPreview();
            //wxMessageBox("preview reset 1");
            previewreset = false;
            previewreset2 = true;
		}



    } else {

        moConfig dummy;
        if (m_pResourceManager) {
            if (!m_pResourceManager->Initialized())
                m_pResourceManager->Init( moText(""), moText("../../data/test") , dummy, 0, 800, 600, 800, 600 );

            if (m_pResourceManager->GetModelMan()) {
                m_pResourceManager->GetModelMan()->MoldeoLogo(m_timerticks);
                GLSwapBuffers();
            }


        }

    }
    return MO_DIRECTOR_STATUS_OK;
}


moDirectorStatus moDirectorConsole::AddPreconfig( moMobDescriptor p_MobDesc, moPreconfigDescriptor p_PreConfDesc ) {

    ///look for the effect parameter
    moMoldeoObject* pObj = GetObject( p_MobDesc );

    if (pObj) {
            moConfig* pConf = pObj->GetConfig();
            if (pConf) {
                pConf->AddPreconfig( p_PreConfDesc.GetPreconfigParams() );
            }
    }

    return MO_DIRECTOR_STATUS_OK;
}


