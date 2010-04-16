#include "moIDirectorActions.h"
#include "moArray.h"

moDefineDynamicArray( moResourceDescriptors )
moDefineDynamicArray( moMobDescriptors )
moDefineDynamicArray( moParameterDescriptors )
moDefineDynamicArray( moValueDescriptors )


void moTextureDescriptor::SetSpecificParameters( MOint p_Width,
                                    MOint p_Height,
                                    MOint p_Components,
                                    MOint m_Index,
                                    MOuint m_GLIndex,
                                    moTexParam m_param,
                                    bool    p_bBuildedFromFile ) {

    moDatas& m_Datas(GetResourceDefinition().GetDatas());

    m_Datas.Empty();

    m_Datas.Add( moData( p_Width ) );//0
    m_Datas.Add( moData( p_Height ) );//1
    m_Datas.Add( moData( p_Components ) );//2
    m_Datas.Add( moData( m_Index ) );//3
    m_Datas.Add( moData( (MOint)m_GLIndex ) );//4
    m_Datas.Add( moData( m_param.internal_format ) );//5
    m_Datas.Add( moData( m_param.mag_filter ) );//6
    m_Datas.Add( moData( m_param.min_filter ) );//7
    m_Datas.Add( moData( (MOint)m_param.target ) );//8
    m_Datas.Add( moData( m_param.wrap_s ) );//9
    m_Datas.Add( moData( m_param.wrap_t ) );//10
    m_Datas.Add( moData( (MOint)p_bBuildedFromFile ) );//11

}

moTexParam& moTextureDescriptor::GetTexParam() {

    moDatas& m_Datas(GetResourceDefinition().GetDatas());

    moTexParam TParam;
    TParam.internal_format = m_Datas[5].Int();
    TParam.mag_filter = m_Datas[6].Int();
    TParam.min_filter = m_Datas[7].Int();
    TParam.target = m_Datas[8].Int();
    TParam.wrap_s = m_Datas[9].Int();
    TParam.wrap_t = m_Datas[10].Int();

    return TParam;
}

MOuint moTextureDescriptor::GetWidth() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[0].Int();
}

MOuint moTextureDescriptor::GetHeight() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[1].Int();
}

MOuint moTextureDescriptor::GetComponents() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[2].Int();
}

MOint moTextureDescriptor::GetIndex() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[3].Int();
}

MOuint moTextureDescriptor::GetGLIndex() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[4].Int();
}

bool moTextureDescriptor::IsBuildedFromFile() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return (m_Datas[11].Int() > 0);
}


//======================
// mo3dModelDescriptor
//======================

void mo3dModelDescriptor::SetSpecificParameters( MOfloat p_Size_X,
                            MOfloat p_Size_Y,
                            MOfloat p_Size_Z,
                            MOint m_Index,
                            mo3dModelParam m_param ) {

    moDatas& m_Datas(GetResourceDefinition().GetDatas());

    m_Datas.Empty();

    m_Datas.Add( moData ( p_Size_X ));
    m_Datas.Add(  moData ( p_Size_Y));
    m_Datas.Add( moData ( p_Size_Z ));
    m_Datas.Add( moData ( m_Index ));

    m_Datas.Add(  moData ( (MOint)m_param.nObjects ));
}

MOfloat mo3dModelDescriptor::GetSizeX() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[0].Float();
}

MOfloat mo3dModelDescriptor::GetSizeY() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[1].Float();
}

MOfloat mo3dModelDescriptor::GetSizeZ() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[2].Float();
}


MOint mo3dModelDescriptor::GetIndex() {
    moDatas& m_Datas(GetResourceDefinition().GetDatas());
    return m_Datas[3].Float();
}

mo3dModelParam& mo3dModelDescriptor::Get3dModelParam() {

    moDatas& m_Datas(GetResourceDefinition().GetDatas());

    mo3dModelParam s3dParam;

    s3dParam.nObjects = m_Datas[4].Int();

    return s3dParam;

}


//======================
// moShaderDescriptor
//======================


void moShaderDescriptor::SetSpecificParameters( MOint m_Index,
                            moText p_VertexShader,
                            moText p_FragmentShader
                             ) {

    moDatas& m_Datas(GetResourceDefinition().GetDatas());

    m_Datas.Empty();

    m_Datas.Add(  moData ( m_Index ));
    m_Datas.Add(  moData ( p_VertexShader ));
    m_Datas.Add(  moData ( p_FragmentShader ));

}
