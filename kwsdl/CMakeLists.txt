
macro_optional_add_subdirectory( doc )
add_subdirectory( wsdl )
add_subdirectory( wscl )
add_subdirectory( kung )


########### next target ###############

set( kwsdl_compiler_SRCS
   compiler.cpp
   converter.cpp
   converter_attribute.cpp
   converter_clientstub.cpp
   converter_complextype.cpp
   converter_element.cpp
   converter_serverstub.cpp
   converter_simpletype.cpp
   converter_transport.cpp
   converter_utils.cpp 
   creator.cpp
   main.cpp
   namemapper.cpp
   settings.cpp
   typemap.cpp )


kde4_add_executable( kwsdl_compiler ${kwsdl_compiler_SRCS} )

target_link_libraries( kwsdl_compiler  ${KDE4_KDECORE_LIBS} ${KDE4_KDE3SUPPORT_LIBRARY} kode wsdl schema )

install( TARGETS kwsdl_compiler  ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES kwsdl_compiler.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
