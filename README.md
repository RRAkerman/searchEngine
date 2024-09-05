# LOCAL FILE SEARCH ENGINE
- The search engine is a console application (an executable file that runs on any server or computer),
    performing searches and having the ability to configure via JSON files.
- The solutions used in it can subsequently be integrated into a search engine running on the web.

## Bsic configuration DATA

- Name(default):			Owl
- Version: 			1.0
- Max responses(default): 	5
- Platform: 			Windows/Linux

## Technologies in the stack

- Programming language: C++
- Libraries:
    - Standard C++ library:
        - fstream
        - vector
		- filesystem
		- exception
		- iostream
		- sstream
		- algorithm
		- map
		- mutex
		- thread
	- Library for working with JSON files:
	    - nlohmann/json.hpp
	- GoogleTest testing library:
	    - gtest/gtest.h

## First run

1. Build the project using **CmakeLists.txt**.
2. Add the "requests.json" file with requests to the "json" folder.
    - **IMPORTANT**:
        - Maximum requests in the file "requests.json" 1000.
        - Request, maximum 10 words long.
        - Word, maximum 100 characters long. In lower case. Allowed characters "a-z".
3. Fill the "resources" folder with files in the format **file001.txt" (where "..001.." is the document serial number)**, 
they will be searched.
    - **IMPORTANT**:
        - A maximum of 1000 words will be selected from one file.
    	- Word, maximum 100 characters long. In lower case. Allowed characters "a-z".
	
4. Run the file from **main.cpp**.
5. Select command 2 **Update database**.
6. Select command 1 **Search**.
7. To finish work, select command 3 **Stop engine**

## Control commands:

1. **Search**: 
    - Starts a search by requests in files. The result of the work is written to **"../json/answers.json"** or **"..\json\answers.json"**.
2. **Update database**:
	- Updates paths to resource files.
3. **Stop engine**:
	- Quits the program with code 0.
>**IMPORTANT**: The directory of JSON files, **"../json/.."** or **"..\json\.."**.
>**IMPORTANT**: The templates of the JSON files **config.json**, **requests.json**, **answers.json** are located at the path **"../json/README.txt"** or **"..\json\README.txt"**.

## EXCEPTION HANDLING
    Config file is missing
- Check the configuration file for existence. If missing, create according to the **config.json** template.
#    
    Config file is empty
- Check the configuration file for correct filling according to the **config.json** template.
#
    Missing paths to resource files
- See ***First run***, item 3, item 4, item 5.
#
    The resource directory is empty or missing
- Check for the presence of the **"../resources"** or **"..\resources"** folder:
    - If missing, create a folder named "resources" in the project folder, see ***First run***, item 3.
    - If the folder exists, see ***First run***, item 3.
#
    Update the path to resource files
- See ***First run***, item 5.
#
    File requests.json is missing
- Check if the file exists. If not, create/add according to the **requests.json** template.
#
    File requests.json is empty
- Open the file, fill in according to the **requests.json** template.
#
    Incorrect request structure
- Open the **requests.json** file, erase all contents, fill in according to the **requests.json** template.
## CONCLUSION
- Enjoy using it.
