# Quellcode-Dateien definieren
set(kloudspeaker_SRCS
    main.cpp
    kloudspeakerwindow.cpp
    kloudspeakerview.cpp
    driver.cpp
)

# Logging-Kategorie hinzufügen
ecm_qt_declare_logging_category(kloudspeaker_SRCS
    HEADER kloudspeakerdebug.h
    IDENTIFIER KLOUDSPEAKER
    CATEGORY_NAME "kloudspeaker"
)

# KCFG-Dateien generieren
find_program(KCONFIG_COMPILER_EXECUTABLE NAMES kconfig_compiler_kf5 REQUIRED PATHS /usr/lib64/libexec/kf5/)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/kloudspeakerSettings.h
           ${CMAKE_CURRENT_BINARY_DIR}/kloudspeakerSettings.cpp
    COMMAND ${KCONFIG_COMPILER_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/kloudspeakerSettings.kcfg
            ${CMAKE_CURRENT_SOURCE_DIR}/kloudspeakerSettings.kcfgc
            --directory ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/kloudspeakerSettings.kcfg
            ${CMAKE_CURRENT_SOURCE_DIR}/kloudspeakerSettings.kcfgc
    COMMENT "Generating kloudspeakerSettings.h and kloudspeakerSettings.cpp"
)

# Generierte Dateien hinzufügen
list(APPEND kloudspeaker_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/kloudspeakerSettings.cpp
)

# Generierte Dateien als GENERATED markieren
set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/kloudspeakerSettings.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/kloudspeakerSettings.h
    PROPERTIES GENERATED TRUE
)

# Include-Verzeichnisse hinzufügen
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# UI-Dateien verarbeiten
ki18n_wrap_ui(kloudspeaker_SRCS
    kloudspeakerview.ui
    settings.ui
)

# Executable erstellen
add_executable(kloudspeaker ${kloudspeaker_SRCS})

# Benötigte Bibliotheken einbinden
target_link_libraries(kloudspeaker
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
    KF5::DBusAddons
    KF5::Crash
    Qt5::Widgets
)

# Installationsanweisungen
install(TARGETS kloudspeaker ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.example.kloudspeaker.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.example.kloudspeaker.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES kloudspeakerui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/kloudspeaker)
