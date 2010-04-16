#include "moEffectConfig.h"



bool moMobConfig::Init( moMobDescriptor p_MobDescriptor) {

	m_MobDescriptor = p_MobDescriptor;

	return true;
}



void
moMobConfig::SetConfigFullText() {

    char tmp[1024];
	moText* ptextmemo = new moText();
    moText lineacfg;
    FILE *configfile;

	if( IsConfigLoaded() ) {	

		if(!(configfile = fopen( m_MobDescriptor.GetFullConfigName(), "rt")))
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
		m_MobDescriptor.SetFullText(ptextmemo);
		
	}
	return;

}



bool moMobConfig::LoadConfig( moMobDescriptor p_MobDescriptor )  {

	if( m_Config.LoadConfig( p_MobDescriptor.GetFullConfigName() ) == MO_CONFIG_OK ) {
		
		m_MobDescriptor = p_MobDescriptor;

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

	return false;
}



bool moMobConfig::SaveAsConfig( moText p_confignewname ) {

	return false;
}



bool moMobConfig::IsConfigLoaded() {

	return (bool)m_Config.IsConfigLoaded();
}



bool moMobConfig::Finish() {

	return UnloadConfig();
}		
