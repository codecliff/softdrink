
# ####################################################
# Author    : Rahul Singh 
# URL       : https://github.com/codecliff/softdrink
# License   : MIT 
# email     : codecliff@users.noreply.github.com
# Disclaimer: No warranties, stated or implied.   
# Description : 
#   This File is part of softdrink project
#   A personal attempt to create directory shortcuts 
#   for Gnome and Nautilus file browser 
#   (Acknowledgment: This project has heavily used LLMs 
#                    viz. Phind, Bard and ChatGPT )
# #####################################################

# #####################################################
# Start development  build with this file
# Not needed for install 
# Version number update to be done in  configure.ac
# #####################################################



# SHELL = /bin/bash
SUBDIRS = src

EXTRA_DIST = assets

AUTOMAKE_OPTIONS = foreign


# in if - else, use \ as make takes each line as separate command
# indents are very important for scoping 
# use double $$ for shell variables
# also, no comments inside the hook
# target rah_conditional_hook_install is run conditional on os type


###### Prepare  different stuff for Ubuntu vs others  #########
# OS  (Ubuntu / Fedora Linux etc) 
RAH_OS = $(shell grep -oP '^NAME.\"\K.*(?=\")' /etc/os-release)


############################################
# Conditional hooks for Installation 
############################################

# Demarcate diferent targets for different OSs
rah_os_dep_target_install = $(if $(filter Ubuntu,$(RAH_OS)),rah_ubuntu_hook_install,rah_nonubuntu_hook_install)



# Define os-specific instalaltion  parts 
rah_ubuntu_hook_install:
	@echo "OS is Ubuntu" 
	@echo "Installing custom mime  for all users"
	sudo cp  ./assets/application-x-jump_ubuntu.xml /usr/share/mime/packages/application-x-jump.xml 
	sudo update-icon-caches /usr/share/icons  
	sudo update-icon-caches /usr/share/icons/hicolor 

rah_nonubuntu_hook_install:
	@echo "OS Not Ubuntu" 
	sudo cp  ./assets/application-x-jump_others.xml /usr/share/mime/packages/application-x-jump.xml 
	@echo " Resorting to gtk-update-icon-cache \n" 
	sudo gtk-update-icon-cache -tf /usr/share/icons 
	sudo gtk-update-icon-cache -tf /usr/share/icons/hicolor 


# to call these parts, run this
rah_conditional_hook_install: $(rah_os_dep_target_install)

############################################
# Conditional hooks for uninstallation 
############################################

rah_ubuntu_hook_uninstall:
	@echo "OS is Ubuntu" 
	@echo "UnInstalling custom mime  for all users"	
	sudo update-icon-caches /usr/share/icons  
	sudo update-icon-caches /usr/share/icons/hicolor 

rah_nonubuntu_hook_uninstall:
	@echo "OS Not Ubuntu" 	
	sudo gtk-update-icon-cache -tf /usr/share/icons 
	sudo gtk-update-icon-cache -tf /usr/share/icons/hicolor 

# Demarcate diferent targets for different OSs
rah_os_dep_target_uninstall = $(if $(filter Ubuntu,$(RAH_OS)),rah_ubuntu_hook_uninstall,rah_nonubuntu_hook_uninstall)
# to call these parts, run this
rah_conditional_hook_uninstall: $(rah_os_dep_target_uninstall)



#########################################################
################## Installation ########################
#########################################################
install-exec-hook:
	@echo "Going to  install custom mime and icons for all users"
	@echo "Installing .desktop file  for all users"
	sudo cp ./assets/softdrink.desktop /usr/share/applications/
	sudo chmod 755 /usr/share/applications/softdrink.desktop

	@echo "Installing   icon  for all users"
	sudo cp ./assets/softdrink.svg /usr/share/icons/softdrink.svg
	sudo chmod 644 /usr/share/icons/softdrink.svg
	sudo cp ./assets/softdrink.png /usr/share/icons/softdrink.png
	sudo chmod 644 /usr/share/icons/softdrink.png

	sudo cp ./assets/softdrink.svg /usr/share/icons/hicolor/scalable/mimetypes/application-x-jump.svg
	sudo chmod 644 /usr/share/icons/hicolor/scalable/mimetypes/application-x-jump.svg	

	$(MAKE) rah_conditional_hook_install

	@echo "Updating mime and desktop  databases etc:"
	sudo update-mime-database /usr/share/mime
	sudo update-desktop-database /usr/share/applications

	@echo "Done with install-exec-hook"


##########################################################
################## Unisntallation ########################
##########################################################	
uninstall-hook:

	@echo "Removing custom mime  for all users"

	sudo rm -f /usr/share/mime/packages/application-x-jump.xml
	sudo rm  -f /usr/share/mime/application/x-jump.xml

	@echo "Removing softdrink.desktop file  for all users"
	sudo rm -f /usr/share/applications/softdrink.desktop

	@echo "Removing  scalable icon  for all users"
	sudo rm -f /usr/share/icons/softdrink.svg
	sudo rm -f /usr/share/icons/softdrink.png
	sudo rm -f /usr/share/icons/hicolor/scalable/mimetypes/application-x-jump.svg
	
	@echo "Updating mime databases etc:"
	sudo update-mime-database /usr/share/mime
	sudo update-desktop-database /usr/share/applications

	$(MAKE) rah_conditional_hook_uninstall

	@echo "Done with uninstall-hook"






	
	
