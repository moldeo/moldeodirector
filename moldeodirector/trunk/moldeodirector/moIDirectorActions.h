/*******************************************************************************

                                moIDirectorActions.h

  ****************************************************************************
  *                                                                          *
  *   This source is free software; you can redistribute it and/or modify    *
  *   it under the terms of the GNU General Public License as published by   *
  *   the Free Software Foundation; either version 2 of the License, or      *
  *  (at your option) any later version.                                    *
  *                                                                          *
  *   This code is distributed in the hope that it will be useful, but       *
  *   WITHOUT ANY WARRANTY; without even the implied warranty of             *
  *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
  *   General Public License for more details.                               *
  *                                                                          *
  *   A copy of the GNU General Public License is available on the World     *
  *   Wide Web at <http://www.gnu.org/copyleft/gpl.html>. You can also       *
  *   obtain it by writing to the Free Software Foundation,                  *
  *   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.         *
  *                                                                          *
  ****************************************************************************

  Copyright(C) 2006 Fabricio Costa

  Authors:
  Fabricio Costa
  Andr�s Colubri

  Description:
	Interface for director actions, Core and Frames will inherit from this class

*******************************************************************************/
#ifndef _MO_DIRECTORACTIONS_
#define _MO_DIRECTORACTIONS_

#include "moDirectorTypes.h"
#include <wx/platform.h>
#include <wx/string.h>
#include <wx/snglinst.h>
#include <wx/filename.h>
#include <wx/app.h>

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class moDirectorApp : public wxApp
{
public:

	// override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization(doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
    virtual int OnExit();
    wxSingleInstanceChecker* m_checker;
};

//DECLARE_APP(moDirectorApp)

#define MO_ITEM_ID_UNDEFINED		65536

enum moDirectorStatus {
	MO_DIRECTOR_STATUS_FALSE = 0,
	MO_DIRECTOR_STATUS_TRUE = 1,
	MO_DIRECTOR_STATUS_OK = 1,
	MO_DIRECTOR_STATUS_ERROR = 2,
	MO_DIRECTOR_STATUS_CONFIG_ALREADY_LOADED = 4,
	MO_DIRECTOR_STATUS_CONFIG_ERROR = 8,
	MO_DIRECTOR_STATUS_CONFIG_ALREADY_OPENED = 16,
	MO_DIRECTOR_STATUS_NOT_FOUND = 32,
	MO_DIRECTOR_STATUS_NO_PROJECT = 64,
	MO_DIRECTOR_STATUS_NO_HANDLER = 128,
	MO_DIRECTOR_STATUS_MOB_NOT_FOUND = 256
};

#define CHECK_DIRECTOR_STATUS_ERROR( X, Y ) (moDirectorStatus)((int)X | (int)Y)

/*
class moDirectorStatus {
	public:

};
*/

class   moApplicationDescriptor {

    public:

        moApplicationDescriptor() {
            m_InstallationFullPath = moText("");
            m_PluginsFullPath = moText("");
        }

        moApplicationDescriptor( moText p_InstallationFullPath, moText p_PluginsFullPath) {
            m_InstallationFullPath = p_InstallationFullPath;
            m_PluginsFullPath = p_PluginsFullPath;
        }

        moApplicationDescriptor & operator = (const moApplicationDescriptor &src) {
                m_InstallationFullPath = src.m_InstallationFullPath;
                m_PluginsFullPath = src.m_PluginsFullPath;
                m_PluginDefinitions = src.m_PluginDefinitions;
                return *this;
        }

        virtual ~moApplicationDescriptor() {

        }
        moPluginDefinitions& GetPluginDefinitions() {
            return m_PluginDefinitions;
        }
        moText GetInstallationFullPath() {
                return m_InstallationFullPath;
        }
        moText GetPluginsFullPath() {
                return m_PluginsFullPath;
        }

    protected:

        moPluginDefinitions         m_PluginDefinitions;///lista de definiciones de plugins existentes
        moText                      m_InstallationFullPath;///base para localizar plugins
        moText                      m_PluginsFullPath;///directorio de plugins (INSTALLPATH/plugins/)


};

class  moProjectDescriptor {

public:

	moProjectDescriptor() {
		m_configname = moText("");
		m_configpath = moText("");
		m_fullconfigname = moText("");
	}

	moProjectDescriptor( moText p_fullconfigname ) {
		//atencion falta sacar el p_configname y el p_configpath del p_fullconfigname
		const char *aux = p_fullconfigname;
		wxString fcname((wxChar*)aux);
		wxFileName FileName(fcname);
		wxString name = FileName.GetFullName();
		wxString path = FileName.GetPath() + wxT("\\");
		const char *cfilepath = (char*)path.c_str();
		const char *cfilename = (char*)name.c_str();
		m_configname = moText((char*)cfilename);
		m_configpath = moText((char*)cfilepath);
		m_fullconfigname = p_fullconfigname;
	}

    moProjectDescriptor& operator = ( const moProjectDescriptor& mpd) {

        m_configname = mpd.m_configname;
        m_configpath = mpd.m_configpath;
        m_fullconfigname = mpd.m_fullconfigname;

        return(*this);
    }

	moProjectDescriptor( moText p_configname, moText p_configpath) {
		m_configname = p_configname;
		m_configpath = p_configpath;
		m_fullconfigname = (moText)p_configpath + (moText)p_configname;
	}

	void Set( moText p_configpath, moText p_configname ) {
		m_configname = p_configname;
		m_configpath = p_configpath;
		m_fullconfigname = (moText)p_configpath + (moText)p_configname;
	}

	const moText& GetConfigName() const { return m_configname; }
	const moText& GetConfigPath() const { return m_configpath; }
	const moText& GetFullConfigName() const { return m_fullconfigname; }

	MOint GetMobsCount(moResourceType) { return 0; }; // TODO: Que debe devolver?

//REQUIRED MEMBERS TO GetProject
public:
	//config name
	moText m_configname;
	//description
	moText m_configpath;
	//config full name
	moText m_fullconfigname;

};


class moMobState {

    public:

        moMobState() {}
        moMobState( const moMobState& pstate) {
            (*this) = pstate;
        }
        moMobState( moEffectState& p_EffectState ) {
            m_EffectState = p_EffectState;
        }
        moMobState( moMobState& p_State ) {
            m_EffectState = p_State.m_EffectState;
        }
        virtual ~moMobState() {}

        moEffectState&  GetEffectState() {
            return m_EffectState;
        }

    private:

        moEffectState   m_EffectState;

        //moConsoleState ???

        //otros valores necesarios
        //bool loading;
        //bool opening;
        //bool drawing;
        //bool initializing;
        //bool etc....


};

class moResourceDefinition {

    public:
        moResourceDefinition() :
        m_ResourceType(MO_RESOURCETYPE_UNDEFINED),
        m_ResourceName(""),
        m_ResourceFileName(""),
        m_ResourceSize(0),
        m_ResourceReservedType(0),
        m_ResourceReservedName("") {

        }

        moResourceDefinition( moResourceType p_ResourceType,
                              moText        p_ResourceName,
                              moText        p_FileName,
                              MOint        p_Size,
                              MOint        p_ResourceReservedType,
                              moText        p_ResourceReservedName
                              ) :
        m_ResourceType(p_ResourceType),
        m_ResourceName(p_ResourceName),
        m_ResourceFileName(p_FileName),
        m_ResourceSize(p_Size),
        m_ResourceReservedType(p_ResourceReservedType),
        m_ResourceReservedName(p_ResourceReservedName) {

        }
        virtual ~moResourceDefinition() {

        }

        moResourceDefinition& operator= (const moResourceDefinition& pResDef) {
            m_ResourceType = pResDef.m_ResourceType;
            m_ResourceName = pResDef.m_ResourceName;
            m_ResourceFileName = pResDef.m_ResourceFileName;
            m_ResourceSize = pResDef.m_ResourceSize;
            m_ResourceReservedType = pResDef.m_ResourceReservedType;
            m_ResourceReservedName = pResDef.m_ResourceReservedName;
            m_Datas = pResDef.m_Datas;
            return (*this);
        }

        moDatas&    GetDatas() {
                return m_Datas;
        }

        moText GetName() {
            return m_ResourceName;
        }

        moResourceType GetType() {
            return m_ResourceType;
        }

        moText GetFileName() {
            return m_ResourceFileName;
        }

        MOint GetSize() {
            return m_ResourceSize;
        }

        MOint GetReservedType() {
            return m_ResourceReservedType;
        }

        moText GetReservedName() {
            return m_ResourceReservedName;
        }

    private:
        moResourceType  m_ResourceType;
        moText          m_ResourceName;
        moText          m_ResourceFileName; //caso general son recursos f�sicos, archivos...
        MOint           m_ResourceSize;//una idea del peso que tiene

        MOint           m_ResourceReservedType; //for special needs:
        moText          m_ResourceReservedName; //for special needs: for example: video FOURCC, DVSD, MOVI,

        moDatas         m_Datas;//datas....: lots of....

        friend class moResourceDescriptor;
        friend class moTextureDescriptor;
        friend class mo3dModelDescriptor;
        friend class moShaderDescriptor;
};

class moResourceDescriptor {

    public:

        moResourceDescriptor() : m_ItemIndex(-1),
            m_ParentItemIndex(-1),
            m_pItemData(NULL),
            m_bCreateThumbnail(false),
            m_pThumbnail(NULL) {
        }

        moResourceDescriptor( const moResourceDescriptor &pResourceDescriptor ) {
            (*this) = pResourceDescriptor;
        }

        moResourceDescriptor( const moResourceDefinition &pResourceDefinition ) {
            m_ResourceDefinition = pResourceDefinition;
        }

        virtual ~moResourceDescriptor() {}


        moResourceDefinition&    GetResourceDefinition() {
            return m_ResourceDefinition;
        }

        void    SetResourceDefinition( const moResourceDefinition& p_ResourceDefinition ) {
            m_ResourceDefinition = p_ResourceDefinition;
        }

        moResourceDescriptor& operator= (const moResourceDescriptor& pResDes) {
            m_ResourceDefinition = pResDes.m_ResourceDefinition;
            return (*this);
        }

        void SetItemIndex( int p_itemindex) {
            m_ItemIndex = p_itemindex;
        }

        MOint GetItemIndex() {
            return m_ItemIndex;
        }

        void SetParentItemIndex(int p_parentitemindex) {
            m_ParentItemIndex = p_parentitemindex;
        }

        MOint GetParentItemIndex() {
            return m_ParentItemIndex;
        }

        void SetItemData( void* pointer) {
            m_pItemData = pointer;
        }

        void* GetItemData() {
            return m_pItemData;
        }

        void CreateThumbnail( bool createthumbnail = true ) {
            m_bCreateThumbnail = createthumbnail;
        }

        bool IsCreateThumbnail() {
            return m_bCreateThumbnail;
        }

        void SetThumbnail( void * pThumbnail ) {
            m_pThumbnail = pThumbnail;
        }

        void* GetThumbnail() {
            return m_pThumbnail;
        }

    private:

        moResourceDefinition    m_ResourceDefinition;

        /// Para listas de �ndices en los controles: esta lista
        MOint                   m_ItemIndex;

        /// Para listas de �ndices en los controles: referencia o categor�a o secci�n
        MOint                   m_ParentItemIndex;

        /// Para listas de �ndices en los controles: puntero a item o datos para optimizaci�n
        void*                   m_pItemData;

        bool                    m_bCreateThumbnail;

        void*                   m_pThumbnail;

        friend class moTextureDescriptor;
        friend class mo3dModelDescriptor;
        friend class moShaderDescriptor;

};

moDeclareDynamicArray( moResourceDescriptor, moResourceDescriptors )


class moTextureDescriptor : public moResourceDescriptor {

    public:
        moTextureDescriptor( moText p_Name, moText p_TexFileName = "", MOint p_TexSize=0, moTextureType p_TexType=MO_TYPE_TEXTURE, moText p_TexExtensionName="") {

            m_ResourceDefinition = moResourceDefinition( MO_RESOURCETYPE_TEXTURE,
                              p_Name,
                              p_TexFileName,
                              p_TexSize,
                              p_TexType,
                              p_TexExtensionName );
        }

        virtual ~moTextureDescriptor() {}

        moTextureDescriptor( const moResourceDescriptor &pResourceDescriptor ) {
           m_ResourceDefinition = pResourceDescriptor.m_ResourceDefinition;
        }

        moTextureDescriptor& operator= ( const moResourceDescriptor &pResourceDescriptor ) {
           m_ResourceDefinition = pResourceDescriptor.m_ResourceDefinition;
           return (*this);
        }

        void SetSpecificParameters( MOint p_Width,
                                    MOint p_Height,
                                    MOint p_Components,
                                    MOint m_Index,
                                    MOuint m_GLIndex,
                                    moTexParam m_param,
                                    bool    p_bBuildedFromFile );

        MOuint GetWidth();
        MOuint GetHeight();
        MOuint GetComponents();
        MOint GetIndex();
        MOuint GetGLIndex();
        moTexParam GetTexParam();
        bool    IsBuildedFromFile();

        moTextureType   GetType() {
            return (moTextureType) m_ResourceDefinition.m_ResourceReservedType;
        }



};

class mo3dModelDescriptor : public moResourceDescriptor {

    public:
        mo3dModelDescriptor( moText p_Name, moText p_TexFileName="", MOint p_ModelSize=0, mo3dModelType p_ModelType=MO_MODEL_3DS, moText p_ModelExtensionName="") {
            m_ResourceDefinition = moResourceDefinition( MO_RESOURCETYPE_MODEL,
                              p_Name,
                              p_TexFileName,
                              p_ModelSize,
                              (MOint) p_ModelType,
                              p_ModelExtensionName );
        }
        virtual ~mo3dModelDescriptor() {}

        mo3dModelDescriptor( const moResourceDescriptor &pResourceDescriptor ) {
           m_ResourceDefinition = pResourceDescriptor.m_ResourceDefinition;
        }

        void SetSpecificParameters( MOfloat p_Size_X,
                            MOfloat p_Size_Y,
                            MOfloat p_Size_Z,
                            MOint m_Index,
                            mo3dModelParam m_param );

        MOfloat GetSizeX();
        MOfloat GetSizeY();
        MOfloat GetSizeZ();
        MOint   GetIndex();
        mo3dModelParam Get3dModelParam();
};

class moShaderDescriptor : public moResourceDescriptor {

    public:
        moShaderDescriptor( moText p_Name, moText p_ShaderFileName = "" ) {
            m_ResourceDefinition = moResourceDefinition( MO_RESOURCETYPE_SHADER,
                              p_Name,
                              p_ShaderFileName,
                              0,
                              0,
                              "" );
        }
        virtual ~moShaderDescriptor() {}

        moShaderDescriptor( const moResourceDescriptor &pResourceDescriptor ) {
           m_ResourceDefinition = pResourceDescriptor.m_ResourceDefinition;
        }

    void SetSpecificParameters( MOint m_Index,
                                moText p_VertexShader,
                                moText p_FragmentShader
                                 );

};


class  moMobDescriptor {

public:

	moMobDescriptor() {}
	moMobDescriptor( const moMobDescriptor &pMobDescriptor ) {
		(*this) = pMobDescriptor;
	}
	moMobDescriptor( const moMobDefinition &p_mobdefinition ) {
		m_MobDefinition = p_mobdefinition;
	}
	moMobDescriptor( moProjectDescriptor p_ProjectDescriptor, const moMobDefinition &p_mobdefinition) {
		m_MobDefinition = p_mobdefinition;
		m_ProjectDescriptor = p_ProjectDescriptor;
	}
	moMobDescriptor& operator = ( const moMobDescriptor& mbd) {
		m_MobDefinition = mbd.m_MobDefinition;
		m_ProjectDescriptor = mbd.m_ProjectDescriptor;
		m_MobState = mbd.m_MobState;
		return(*this);
	}
	void SetProjectDescriptor( moProjectDescriptor p_ProjectDescriptor ) {
		m_ProjectDescriptor = p_ProjectDescriptor;
	}
	void SetState( moMobState p_MobState ) {
		m_MobState = p_MobState;
	}
	moMobState GetState( ) { return m_MobState; }

	const moProjectDescriptor& GetProjectDescriptor() const {
		return m_ProjectDescriptor;
	}

	const moMobDefinition& GetMobDefinition() const {
		return m_MobDefinition;
	}

	moMobDefinition& GetMobDefinition() {
		return m_MobDefinition;
	}

	void Set( const moMobDefinition& p_mobdefinition ) {
		m_MobDefinition = p_mobdefinition;
	}

	void Set( moProjectDescriptor p_ProjectDescriptor, const moMobDefinition &p_mobdefinition ) {
		m_ProjectDescriptor = p_ProjectDescriptor;
		m_MobDefinition = p_mobdefinition;
	}

	MOint GetIndex() { return 0; } // TODO: Que deber�a devolver?
	moResourceType GetType() { return moResourceType(); } // TODO: Que deber�a devolver?
	const char *GetFullConfigName() const { return ""; } // TODO: Que deber�a devolver?
	void SetFullText(const moText &) { } // TODO: que dever�a hacer?
private:
	moMobDefinition m_MobDefinition;
	moProjectDescriptor m_ProjectDescriptor;
	moMobState  m_MobState;
};

moDeclareDynamicArray( moMobDescriptor, moMobDescriptors )

class  moParameterDescriptor {

public:

	moParameterDescriptor() {
	    m_indexvalue = -1;
    }
    moParameterDescriptor( const moParameterDescriptor& p_paramdescriptor ) {
        (*this) = p_paramdescriptor;
    }
	moParameterDescriptor( moMobDescriptor p_MobDescriptor, moParamDefinition p_paramdefinition, int p_index, int p_indexvalue ) {

	    m_MobDescriptor = p_MobDescriptor;
	    m_ParamDefinition = p_paramdefinition;
	    m_indexvalue = p_indexvalue;

	    m_ParamDefinition.SetIndex(p_index);
    }
    moMobDescriptor         GetMobDescriptor() {
            return m_MobDescriptor;
    }

	moParamDefinition GetParamDefinition() {
	    return m_ParamDefinition;
    }

	void SetParamDefinition( moParamDefinition paramdefinition ) {
	    m_ParamDefinition = paramdefinition;
    }


    void SetIndex( int pindex) {
        m_ParamDefinition.SetIndex(pindex);
    }
    void SetIndexValue( int pindexvalue ) {
        m_indexvalue = pindexvalue;
    }

    int GetIndex() {
        return m_ParamDefinition.GetIndex();
    }
    int GetIndexValue() {
        return m_indexvalue;
    }

private:

	int m_indexvalue;

	moParamDefinition   m_ParamDefinition;

	moMobDescriptor   m_MobDescriptor;

};

moDeclareDynamicArray( moParameterDescriptor, moParameterDescriptors )

class  moValueDescriptor {

public:

	moValueDescriptor() {}
	moValueDescriptor( const moParameterDescriptor& p_paramdescriptor, moValueIndex p_valueindex ) {

	    m_ValueIndex = p_valueindex;
	    m_ParamDescriptor = p_paramdescriptor;

    }

    moValueIndex& GetValueIndex() {
	    return m_ValueIndex;
    }

	moValue& GetValue() {
	    return m_Value;
    }

	void SetValue( moValue& value ) {
	    m_Value = value;
    }

    moParameterDescriptor& GetParamDescriptor() {
        return m_ParamDescriptor;
    }

    moValueDefinition& GetValueDefinition() {
        return m_ValueDefinition;
    }

    void SetValueDefinition( moValueDefinition p_valuedefinition) {
        m_ValueDefinition = p_valuedefinition;
    }


private:

    moValueDefinition       m_ValueDefinition;

    moValueIndex            m_ValueIndex;
	moValue                 m_Value;

	moParameterDescriptor   m_ParamDescriptor;

};


moDeclareDynamicArray( moValueDescriptor, moValueDescriptors )

class  moPreconfigDescriptor {

public:

	moPreconfigDescriptor() {}
	moPreconfigDescriptor( const moMobDescriptor& p_mobdescriptor ) {

	    m_MobDescriptor =  p_mobdescriptor;

    }

    moPreconfigDescriptor& operator = ( const moPreconfigDescriptor& preconfd) {

        m_MobDescriptor = preconfd.m_MobDescriptor;
        m_PreconfigIndexes = preconfd.m_PreconfigIndexes;
        return(*this);
    }

    moMobDescriptor& GetMobDescriptor() {
	    return m_MobDescriptor;
    }

	moPreconfigIndexes& GetPreconfigParams() {
	    return m_PreconfigIndexes;
    }

    void Add( moPreconfigParamIndex& p_preconfigparam ) {
            m_PreconfigIndexes.Add(p_preconfigparam);
    }
    void Clear() {
            m_PreconfigIndexes.Empty();
    }

private:

    moPreconfigIndexes       m_PreconfigIndexes;
    moMobDescriptor         m_MobDescriptor;

};


class moPresetDescriptor {

public:

	moPresetDescriptor() {}
	moPresetDescriptor( const moProjectDescriptor& p_projectdescriptor ) {
	    m_ProjectDescriptor =  p_projectdescriptor;
    }

    moPresetDescriptor& operator = ( const moPresetDescriptor& presetd) {

        m_ProjectDescriptor = presetd.m_ProjectDescriptor;
        m_PresetParams = presetd.m_PresetParams;
        return(*this);
    }

    void Add( moPresetParamDefinition& p_presetparam ) {
            m_PresetParams.Add(p_presetparam);
    }

    void Clear() {
            m_PresetParams.Empty();
    }

private:

    moProjectDescriptor     m_ProjectDescriptor;
    moPresetParams          m_PresetParams;

};


#define MO_ACTIONHANDLER(F)  m_pNextActionHandler == NULL ? MO_DIRECTOR_STATUS_NO_HANDLER : m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_APPLICATION(F)  m_pNextActionHandler == NULL ? moApplicationDescriptor() : m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_PROJECT(F)  m_pNextActionHandler == NULL ? moProjectDescriptor() : m_pNextActionHandler->F;

#define MO_ACTIONHANDLER_MOB(F)  m_pNextActionHandler == NULL ? moMobDescriptor() : m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_MOBS(F)  m_pNextActionHandler == NULL ? moMobDescriptors() : m_pNextActionHandler->F;

#define MO_ACTIONHANDLER_RESOURCE(F)  m_pNextActionHandler == NULL ? moResourceDescriptor() : m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_RESOURCES(F)  m_pNextActionHandler == NULL ? moResourceDescriptors() : m_pNextActionHandler->F;

#define MO_ACTIONHANDLER_PARAM(F)  m_pNextActionHandler == NULL ? moParameterDescriptor() : m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_PARAMS(F)  m_pNextActionHandler == NULL ? moParameterDescriptors() : m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_VALUE(F)  m_pNextActionHandler == NULL ? moValueDescriptor() : m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_VALUES(F)  m_pNextActionHandler == NULL ? moValueDescriptors() : m_pNextActionHandler->F;

#define MO_ACTIONHANDLER_POINTER(F)  m_pNextActionHandler == NULL ? NULL : m_pNextActionHandler->F;

#define MO_ACTIONHANDLER_VOID(F)  if (m_pNextActionHandler) m_pNextActionHandler->F;
#define MO_ACTIONHANDLER_HANDLE(F)  m_pNextActionHandler == NULL ? NULL : m_pNextActionHandler->F;



class moIDirectorActions {

public:

	moIDirectorActions() { m_pNextActionHandler = NULL; }
	virtual ~moIDirectorActions() {}

	void SetNextActionHandler( moIDirectorActions* p_pNextActionHandler ) { m_pNextActionHandler = p_pNextActionHandler; }

public:



//=========================================================================================================================
//NEW IDIRECTORACTIONS
//=========================================================================================================================

	//virtual moResourceManager*			GetCore() { return MO_ACTIONHANDLER_POINTER(GetResourceManager()); }

	virtual moDirectorStatus Preview() { return MO_ACTIONHANDLER(Preview()); }//to the DirectorConsole
	virtual moDirectorStatus FullScreen(bool force=false) { return MO_ACTIONHANDLER(FullScreen()); }

	virtual moDirectorStatus InitPreview() { return MO_ACTIONHANDLER(InitPreview()); }
	virtual moDirectorStatus DrawPreview() { return MO_ACTIONHANDLER(DrawPreview()); }

	virtual moDirectorStatus ConsoleLoop() { return MO_ACTIONHANDLER(ConsoleLoop()); }
	virtual moDirectorStatus SetView( int x, int y, int w, int h ) { return MO_ACTIONHANDLER(SetView(x,y,w,h)); }
	virtual void ViewSwapBuffers() { MO_ACTIONHANDLER_VOID(ViewSwapBuffers()); }
	virtual MO_HANDLE GetHandle() { return MO_ACTIONHANDLER_HANDLE(GetHandle()); }

    /**
    *   Hace foco sobre la ventana
    */
	virtual moDirectorStatus FocusOutput() { return MO_ACTIONHANDLER(FocusOutput()); }

    /**
    *   Este play simplemente deja corriendo el loop
    */
	virtual moDirectorStatus Play() { return MO_ACTIONHANDLER(Play()); }

    /**
    *   Parar el loop principal
    */
    virtual moDirectorStatus Stop() { return MO_ACTIONHANDLER(Stop()); }

    /**
    *   Pausa del loop principal
    *   queda por verse si simplemente congelamos el clock
    *   o bien congelamos el loop (esto puede ser una opci�n dentro de la configuraci�n del proyecto)
    *   o 2 botones diferenciados...
    */
    virtual moDirectorStatus Pause() { return MO_ACTIONHANDLER(Pause()); }

    /**
    *   Salvar en disco la sesi�n visualizada, luego podr� ser reproducida...
    */
    virtual moDirectorStatus SaveSession() { return MO_ACTIONHANDLER(SaveSession()); }

    /**
    *   Parar el loop principal
    */
    virtual moDirectorStatus Seek( MOulong p_timecode ) { return MO_ACTIONHANDLER(Seek( p_timecode )); }

    /**
    *   Salvar todos los efectos abiertos, y el proyecto.
    */
	virtual moDirectorStatus SaveAll() { return MO_ACTIONHANDLER(SaveAll()); }


	virtual moDirectorStatus CloseAll() { return MO_ACTIONHANDLER(CloseAll()); }

	virtual moDirectorStatus CloseApp() { return MO_ACTIONHANDLER(CloseApp()); }

    virtual moApplicationDescriptor GetApplicationDescriptor() { return MO_ACTIONHANDLER_APPLICATION(GetApplicationDescriptor()); }

//================================================================
//Project
//================================================================
	virtual moDirectorStatus NewProject( moProjectDescriptor p_projectdescriptor ) { return MO_ACTIONHANDLER(NewProject(p_projectdescriptor)); }
	virtual moDirectorStatus OpenProject( moProjectDescriptor p_projectdescriptor ) { return MO_ACTIONHANDLER(OpenProject(p_projectdescriptor)); } //load a console.mol file with their effects.cfg
	virtual moDirectorStatus CloseProject() { return MO_ACTIONHANDLER(CloseProject()); } //load a console.mol file with their effects.cfg
	virtual moDirectorStatus SaveProject() { return MO_ACTIONHANDLER(SaveProject()); } //save a console.mol file with their effects.cfg
	virtual moDirectorStatus SaveAsProject( moText p_configname, moText p_configpath ) { return MO_ACTIONHANDLER(SaveAsProject(p_configname,p_configpath)); } //save a console.mol file with their effects.cfg
	virtual moDirectorStatus ProjectUpdated( moProjectDescriptor p_projectdescriptor ) { return MO_ACTIONHANDLER(ProjectUpdated(p_projectdescriptor)); }

	virtual moDirectorStatus SetProject( moProjectDescriptor p_projectdescriptor ) { return MO_ACTIONHANDLER(SetProject(p_projectdescriptor)); } //
	virtual moProjectDescriptor GetProject() { return MO_ACTIONHANDLER_PROJECT(GetProject()); } //
	virtual moDirectorStatus ReloadProject() { return MO_ACTIONHANDLER(ReloadProject()); } //

	virtual moDirectorStatus ProjectPreview( ) { return MO_ACTIONHANDLER(ProjectPreview()); }
	virtual moDirectorStatus EffectPreview( MOint p_n ) { return MO_ACTIONHANDLER(EffectPreview(p_n)); }

    virtual moMobDescriptors GetMobDescriptors() { return MO_ACTIONHANDLER_MOBS(GetMobDescriptors()); }

//================================================================
// Resources...
//================================================================

    virtual moResourceDescriptor GetResourceDescriptor( moResourceDescriptor p_ResourceDescriptor ) { return MO_ACTIONHANDLER_RESOURCE( GetResourceDescriptor( p_ResourceDescriptor ) ); }
    virtual moResourceDescriptors GetResourceDescriptors(  moResourceType p_ResourceType  ) { return MO_ACTIONHANDLER_RESOURCES(GetResourceDescriptors(p_ResourceType)); }


//================================================================
//MOB Moldeo Object
//================================================================
    virtual moDirectorStatus ImportMob( moText p_filename ) { return MO_ACTIONHANDLER(ImportMob(p_filename)); }

    /// Abre un MOB ya existente desde un archivo de configuraci�n
	virtual moDirectorStatus OpenMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(OpenMob(p_MobDesc)); }

	/// Cierra un MOB y su archivo de configuraci�n
	virtual moDirectorStatus CloseMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(CloseMob(p_MobDesc)); }

	/// Recarga un MOB desde su archivo de configuraci�n
	virtual moDirectorStatus ReloadMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(ReloadMob(p_MobDesc)); }

    ///crea un nuevo MOB con su respectivo archivo de configuraci�n, desde la lista de plugins
	virtual moDirectorStatus NewMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(NewMob(p_MobDesc)); }

	///edita o abre el MOB que se describe
	virtual moDirectorStatus EditMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(EditMob(p_MobDesc)); }

	///salva al archivo de configuraci�n todos los datos
	virtual moDirectorStatus SaveMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(SaveMob(p_MobDesc)); }

	virtual moDirectorStatus DeleteMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(DeleteMob(p_MobDesc)); }
	virtual moMobDescriptor GetMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER_MOB(GetMob(p_MobDesc)); }
	virtual moDirectorStatus SetMob( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(SetMob(p_MobDesc)); }

/*indica al Core que el Mob especificado ha sido modificado y sus datos deber�n ser actualizados en el DirectorFrame:
este metodo se usa principalmente desde el SessionProject, que deber�a verificar que cada archivo al ser modificado exteriormente el usuario sea notificado
ATENCION: este metodo obligar a recargar completamente el config del efecto....
tanto en la interface como en los DirectorConsole's principal y childs...
*/
	virtual moDirectorStatus MobUpdated( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(MobUpdated(p_MobDesc)); }
/*Add a Mob to the Mol Project*/
	virtual moDirectorStatus AddMobToProject( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(AddMobToProject(p_MobDesc)); }
/*Remove a Mob from the Mol Project*/
	virtual moDirectorStatus RemoveMobToProject( moMobDescriptor p_MobDesc ) {return MO_ACTIONHANDLER(RemoveMobToProject(p_MobDesc)); }
/*Move a Mob from the Mol Project to a different index on Mol Console */
	virtual moDirectorStatus MoveMobInProject( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER(MoveMobInProject(p_MobDesc)); }

    virtual moParameterDescriptors GetParameterDescriptors( moMobDescriptor p_MobDesc ) { return MO_ACTIONHANDLER_PARAMS(GetParameterDescriptors(p_MobDesc)); }

//================================================================
//PARAMETERS
//================================================================
    ///estas funciones son obsoletas...??
	virtual moDirectorStatus NewParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(NewParameter(p_ParameterDesc)); }
	virtual moDirectorStatus InsertParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(InsertParameter(p_ParameterDesc)); }
	virtual moDirectorStatus MoveParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(MoveParameter(p_ParameterDesc)); }
	virtual moDirectorStatus EditParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(EditParameter(p_ParameterDesc)); }
	virtual moDirectorStatus SaveParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(SaveParameter(p_ParameterDesc)); }
	virtual moDirectorStatus SetParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(SetParameter(p_ParameterDesc)); }
	virtual moParameterDescriptor GetParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER_PARAM(GetParameter(p_ParameterDesc)); }
	virtual moDirectorStatus DeleteParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(DeleteParameter(p_ParameterDesc)); }
/*este metodo es usado principalmente por el SessionProject para notificar cualquier cambio de parametro al Core
y que este pueda notificar ese cambio directamente a los DirectorConsole's principal y childs, para que modifiquen unicamente
	ese parametro y no los otros, generalmente un cambio de nombre*/
	virtual moDirectorStatus ParameterUpdated( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(ParameterUpdated(p_ParameterDesc)); }
	virtual moDirectorStatus ReloadParameter( moParameterDescriptor p_ParameterDesc ) { return MO_ACTIONHANDLER(ReloadParameter(p_ParameterDesc)); }

//================================================================
// VALUES
//================================================================
    ///crea un nuevo valor dentro de un par�metro dentro de un config
	virtual moDirectorStatus NewValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(NewValue(p_ValueDesc)); }
	virtual moDirectorStatus InsertValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(InsertValue(p_ValueDesc)); }
	virtual moDirectorStatus EditValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(EditValue(p_ValueDesc)); }
	virtual moDirectorStatus SaveValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(SaveValue(p_ValueDesc)); }
	virtual moValueDescriptor GetValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER_VALUE(GetValue(p_ValueDesc)); }
	virtual moDirectorStatus SetValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(SetValue(p_ValueDesc)); }
/*borra un valor de la lista de un parametro, notifica al Core para actualizar los configs correspondientes*/
	virtual moDirectorStatus DeleteValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(DeleteValue(p_ValueDesc)); }
/*este metodo es usado principalmente por el SessionProject para notificar cualquier cambio de valores de parametros al Core
y que este pueda notificar ese cambio directamente a los DirectorConsole's principal y childs, para que modifiquen sus
configuraciones. Ser� modificado unicamente ese valor, generalmente un cambio de valor...*/
	virtual moDirectorStatus ValueUpdated( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(ValueUpdated(p_ValueDesc)); }
	virtual moDirectorStatus ReloadValue( moValueDescriptor p_ValueDesc ) { return MO_ACTIONHANDLER(ReloadValue(p_ValueDesc)); }

    virtual moValueDescriptors GetValueDescriptors( moParameterDescriptor p_ParamDesc ) { return MO_ACTIONHANDLER_VALUES(GetValueDescriptors(p_ParamDesc)); }


//================================================================
// Effects states
//================================================================

    virtual moDirectorStatus AddPreconfig( moMobDescriptor p_MobDesc, moPreconfigDescriptor p_PreConfDesc ) { return MO_ACTIONHANDLER(AddPreconfig( p_MobDesc, p_PreConfDesc)); }
    virtual moDirectorStatus DeletePreconfig( moMobDescriptor p_MobDesc, moPreconfigDescriptor p_PreConfDesc ) { return MO_ACTIONHANDLER(DeletePreconfig( p_MobDesc, p_PreConfDesc)); }
    virtual moDirectorStatus SavePreconfig( moMobDescriptor p_MobDesc, moPreconfigDescriptor p_PreConfDesc ) { return MO_ACTIONHANDLER(SavePreconfig( p_MobDesc, p_PreConfDesc)); }
    virtual moDirectorStatus SetPreconfig( moMobDescriptor p_MobDesc, moPreconfigDescriptor p_PreConfDesc ) { return MO_ACTIONHANDLER(SetPreconfig( p_MobDesc, p_PreConfDesc)); }

    virtual moDirectorStatus AddPreset( moPresetDescriptor p_PresetDesc ) { return MO_ACTIONHANDLER(AddPreset(p_PresetDesc)); }
    virtual moDirectorStatus DeletePreset( moPresetDescriptor p_PresetDesc ) { return MO_ACTIONHANDLER(DeletePreset(p_PresetDesc)); }
    virtual moDirectorStatus SavePreset( moPresetDescriptor p_PresetDesc ) { return MO_ACTIONHANDLER(SavePreset(p_PresetDesc)); }
    virtual moDirectorStatus SetPreset( moPresetDescriptor p_PresetDesc ) { return MO_ACTIONHANDLER(SetPreset(p_PresetDesc)); }

    //virtual moDirectorStatus SetMobState( moMobState   m_MobState ) { return MO_ACTIONHANDLER(SetMobState(m_MobState)); }
    //virtual moDirectorStatus SetMobState( moMobState   m_MobState ) { return MO_ACTIONHANDLER(SetMobState(m_MobState)); }

//===============================================================
// LOGS
//===============================================================

	/*Log internal: print on log window on UI, on stdout or file on Core...*/
	virtual void Log( moText p_message ) { MO_ACTIONHANDLER_VOID(Log( p_message )) }
	/*Same but specifically an error*/
	virtual void LogError( moText p_message ) { MO_ACTIONHANDLER_VOID(LogError( p_message )) }
	/*Show a message window popup: implemented on UI*/
	virtual void ShowMessage( moText p_message ) { MO_ACTIONHANDLER_VOID(ShowMessage( p_message )) }
	/*Same as ShowMessage but with ok/cancel buttons and bool value return*/
	virtual bool ConfirmMessage( moText p_message ) { return false;}
	/*Same just as popup message for warnings*/
	virtual void AlertMessage( moText p_message ) { MO_ACTIONHANDLER_VOID(AlertMessage( p_message )) }
	/*Same just as popup message for errors*/
	virtual void ErrorMessage( moText p_message ) { MO_ACTIONHANDLER_VOID(ErrorMessage( p_message )) }

private:
	moIDirectorActions*		m_pNextActionHandler;

};


#endif
