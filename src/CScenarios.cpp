#include "CScenarios.h"

/**
 * @brief CScenarios::CScenarios
 * @param parent
 */
CScenarios::CScenarios(QObject *parent) : QObject(parent){
	_scenariosFilePath = "";
	_fileExist = false;
	UpdatePathFromSave();
	if(!FileExist()){
		CreateNewFile();
	}
	ReloadScenarios();
}

/**
 * @brief CScenarios::UpdatePathFromSave
 * Read if a path is saved in the user data, and save it in strSaveFilePath.
 */
void CScenarios::UpdatePathFromSave(void){
	QString strSaveFilePath = QDir::homePath()+"/.sara_ui_data";
	QFile file(strSaveFilePath);

	ROS_INFO("Try to load saved Scenarios Files path from \"%s\".", strSaveFilePath.toUtf8().constData());

	// Trying to open in ReadWrite and Text mode the data file
	if(!QFile::exists(strSaveFilePath)){
		ROS_INFO("Save file do not existe.");
	}else if(!file.open(QFile::ReadOnly | QFile::Text)){
		ROS_INFO("Can't read save file.");
	}else{
		// Test if file is empty
		if(file.size()==0){
			ROS_INFO("Save file is empty.");
		}else{
			//read str stream from save file
			QTextStream in(&file);

			//read XML path from save
			_scenariosFilePath = in.readLine();
			ROS_INFO("Selected file : \"%s\"", _scenariosFilePath.toUtf8().constData());
		}
		file.close();
	}
}

/**
 * @brief CScenarios::FileExist
 * @return return if the file selected exist
 */
bool CScenarios::FileExist(){
	if(_scenariosFilePath.isEmpty()){
		return false;
	}else{
		return QFile::exists(_scenariosFilePath);
	}
}

/**
 * @brief CScenarios::Create	NewFile
 * Create a new Scenarios example page
 */
void CScenarios::CreateNewFile(){
	QFile scenariosFile(_scenariosFilePath);
	if (FileExist()){
		ROS_INFO("File exist !");
	}else if(!scenariosFile.open(QIODevice::WriteOnly)){
		ROS_INFO("Not able to read Scenarios Files scenarios file.");
	}else{
		//file created
		YAML::Emitter out;
		//generating header
		out << YAML::BeginMap;
		out << YAML::Key << "by";
		out << YAML::Value << "Lucas Maurice";
		out << YAML::Key << "date";
		out << YAML::Value << "2017-05-20";
		out << YAML::Key << "Scenarios";
		out << YAML::Value << YAML::BeginSeq ;

		//generating a scenario map
		out << YAML::BeginMap ;
		out << YAML::Key << "name";
		out << YAML::Value << "Teleop";
		out << YAML::Key << "command";
		out << YAML::Value << "roslaunch teleop.launch";
		out << YAML::Key << "uses";
		out << YAML::Value << "0";
		out << YAML::EndMap;

		//generating a scenario map
		out << YAML::BeginMap ;
		out << YAML::Key << "name";
		out << YAML::Value << "Teleop";
		out << YAML::Key << "command";
		out << YAML::Value << "roslaunch teleop.launch";
		out << YAML::Key << "uses";
		out << YAML::Value << "0";
		out << YAML::EndMap;

		//generating footer
		out << YAML::EndSeq;
		out << YAML::EndSeq;
		out << YAML::EndMap;

		scenariosFile.write(out.c_str(), out.size());
		scenariosFile.close();
	}
}

/**
 * @brief CScenarios::ReloadXML
 * Reload the data of the Scenarios Files.
 */
void CScenarios::ReloadScenarios(void){
	//read YAML file
	YAML::Node scenariosFile = YAML::LoadFile(_scenariosFilePath.toStdString());

	//read header usefull values
	if (scenariosFile["by"] && scenariosFile["date"]) {
	  std::cout << "Last update on " << scenariosFile["date"] << " by " << scenariosFile["by"] << ".\n";
	}else if (scenariosFile["date"]) {
		  std::cout << "Last update on " << scenariosFile["date"] << ".\n";
	}else if (scenariosFile["by"]) {
		std::cout << "Last update by " << scenariosFile["by"] << ".\n";
	}

	//read scenarios
	if (!scenariosFile["Scenarios"]) {
	  ROS_INFO("There is no scenarios to load in Scenarios File!");
	}else if(scenariosFile["Scenarios"].size() == 0){
		ROS_INFO("There is no scenarios to load in Scenarios File!");
	}else{
		for (std::size_t i=0 ; i<scenariosFile["Scenarios"].size() ; i++) {
			if(scenariosFile["Scenarios"][i]["name"]){
				//scenariosFile["Scenarios"][i]["command"]
				//scenariosFile["Scenarios"][i]["uses"].as<int>()
				//scenariosFile["Scenarios"][i]["name"]
			}
		}
	}
}
