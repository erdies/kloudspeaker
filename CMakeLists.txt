cmake_minimum_required(VERSION 3.0)

project(kloudspeaker)

set(QT_MIN_VERSION "5.9.0")
set(KF_MIN_VERSION "5.37.0")

set(CMAKE_AUTOUIC ON)




find_package(Qt5 REQUIRED COMPONENTS Widgets) # Füge hier andere Module hinzu, die du benötigst

set(UI_FILES "settings.ui" "kloudspeakerview.ui")

qt5_wrap_ui(UI_HEADERS ${UI_FILES})  # UI-Dateien in Header-Dateien umwandeln




message(STATUS "CMAKE_AUTOUIC is set to: ${CMAKE_AUTOUIC}")


find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets)

find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    ConfigWidgets
    CoreAddons
    Crash
    DBusAddons
    DocTools
    I18n
    XmlGui
)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(icons)

# set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src)

# Make it possible to use the po files fetched by the fetch-translations step
ki18n_install(po)
kdoctools_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

install(FILES kloudspeakerui.rc DESTINATION ${KDE_INSTALL_KXMLGUIDIR}/kloudspeaker)


