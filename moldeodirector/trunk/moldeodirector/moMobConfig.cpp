#include "moMobConfig.h"



bool moMobConfig::Init( moMobDescriptor p_MobDescriptor) {

	m_MobDescriptor = p_MobDescriptor;

	return true;
}

void
moMobConfig::SetMobDescriptor( moMobDescriptor p_MobDescriptor ) {

	m_MobDescriptor = p_MobDescriptor;

}

moMobDescriptor
moMobConfig::GetMobDescriptor() {

	return m_MobDescriptor;

}

void
moMobConfig::SetConfigFullText() {

    char tmp[1024];
	moText* ptextmemo = new moText();
    moText lineacfg;
    FILE *configfile;

	if( IsConfigLoaded() ) {

	    moText fullconfigname;
	    fullconfigname =    m_MobDescriptor.GetProjectDescriptor().GetConfigPath() +
                            moText("\\") +
                            m_MobDescriptor.GetMobDefinition().GetConfigName();

		if(!(configfile = fopen( (char*)fullconfigname, "rt")))
		{
			return;
		}

		while( fgets(tmp, 1024, configfile))
		{
			lineacfg = tmp;
			//lineacfg.Trim();
			(*ptextmemo)+= lineacfg;
			//textmemo+= "\n";
			/*
			switch( lineacfg[0])
			{
				case '#':   // No hacer nada.
					break;
				case '\0':  // No hacer nada.
					break;
				case ':':   // Nuevo parametro.
					AddParam(lineacfg.Mid(1, MO_TXT_COMPLETE));
					actual = GetCurrentParam();
					break;
				default:    // Nuevo value.
					if(actual != MO_PARAM_NOT_SEL)
						AddValue( actual, lineacfg);
					break;
			}
			*/
		}
		//m_MobDescriptor.SetFullText(ptextmemo);

	}
	return;

}



bool moMobConfig::LoadConfig()  {

    moText fullconfigname;

	fullconfigname =    m_MobDescriptor.GetProjectDescriptor().GetConfigPath() +
                        moText("\\") +
                        m_MobDescriptor.GetMobDefinition().GetConfigName();

	if( m_Config.LoadConfig( fullconfigname ) == MO_CONFIG_OK ) {

		//m_MobDescriptor = p_MobDescriptor;

		return true;

	}


	return false;
}



bool moMobConfig::UnloadConfig() {

	if( m_Config.IsConfigLoaded()) {

		m_Config.DeleteConfig();

	}

	return true;

}



bool moMobConfig::SaveConfig() {
    if (this->m_Config.GetName()==moText(""))
        return false;
	return true;
}



bool moMobConfig::SaveAsConfig( moText p_confignewname ) {
    if (p_confignewname==moText(""))
        return false;
	return true;
}



bool moMobConfig::IsConfigLoaded() {

	return (bool)m_Config.IsConfigLoaded();
}



bool moMobConfig::Finish() {

	return UnloadConfig();
}

