include_directories( ${kode_SOURCE_DIR} )

########### next target ###############

set(schema_LIB_SRCS
   annotation.cpp
   attribute.cpp
   complextype.cpp
   element.cpp
   parser.cpp
   simpletype.cpp
   types.cpp
   xmlelement.cpp
   xsdtype.cpp
   attributegroup.cpp
   compositor.cpp)


kde4_add_library( schema SHARED ${schema_LIB_SRCS} )

target_link_libraries( schema ${KDE4_KIO_LIBS} kxmlcommon )
target_link_libraries( schema LINK_INTERFACE_LIBRARIES kxmlcommon )

set_target_properties( schema PROPERTIES VERSION ${GENERIC_LIB_VERSION}
                                        SOVERSION ${GENERIC_LIB_SOVERSION} )

install( TARGETS schema  ${INSTALL_TARGETS_DEFAULT_ARGS} )

########### next target ###############

set( schematest_SRCS schematest.cpp )

kde4_add_executable( schematest NOGUI RUN_UNINSTALLED ${schematest_SRCS} )

target_link_libraries( schematest ${KDE4_KDECORE_LIBS} schema )

install( TARGETS schematest ${INSTALL_TARGETS_DEFAULT_ARGS} )
