cmake_minimum_required(VERSION 3.16) # Aktuelle Mindestversion verwenden, falls möglich

project(kloudspeaker VERSION 1.0 LANGUAGES CXX)

# Set minimum required versions for Qt and KDE Frameworks
set(QT_MIN_VERSION "5.15.0") # Empfohlen: Mindestens Qt 5.15 verwenden
set(KF_MIN_VERSION "5.85.0") # Aktualisieren, wenn möglich

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON) # Automatisch MOC-Dateien generieren
set(CMAKE_AUTORCC ON) # Automatisch Ressourcen-Dateien verarbeiten

# Qt5 finden (Widgets wird als Pflichtmodul angegeben)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Widgets)

# ECM-Modul und KDE Frameworks finden
find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

# Benötigte KF5-Komponenten einbinden
find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    ConfigWidgets
    CoreAddons
    Crash
    DBusAddons
    DocTools
    I18n
    XmlGui
)

# Unterverzeichnisse hinzufügen
add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(icons)

# UI-Dateien, falls erforderlich
set(UI_FILES "settings.ui" "kloudspeakerview.ui")

# Installationsschritte
install(FILES kloudspeakerui.rc DESTINATION ${KDE_INSTALL_KXMLGUIDIR}/kloudspeaker)

# Lokalisierungsunterstützung (PO-Dateien und Dokufiles)
ki18n_install(po)
kdoctools_install(po)

# Zusammenfassung der gefundenen Pakete
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
