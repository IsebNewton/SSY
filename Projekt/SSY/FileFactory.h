#pragma once
#include <string>
#include <list>
#include <map>
#include <sstream>

class FileFactory
{
public:

	/**
	Schreibt eine Zeile in die übergebene Datei.

	@param file Pfad zur Datei.
	@param text Text welcher in eine Zeile geschrieben werden soll.
	*/
	static void writeLine(std::string file, std::string text, const char mode = std::ios::app);

	/**
	Schreibt die übergebenen Value-Wert Paare in die übergebene Datei.

	@param file Pfad zur Datei.
	@param map Key-Value Paare welche in die Datei geschrieben werden soll.
	*/
	template <typename V, typename K>
	static void write(std::string file, std::map<V, K> map, const char mode = std::ios::app);

	/**
	Liest die Datei Zeilenweise in ein String-Array.

	@param file Pfad zur Datei.
	@return String-List Einzelne Zeilen der Datei.
	*/
	static std::list<std::string> readLines(std::string file);

	/**
	Liest die Datei Zeilenweise in eine Map aus Key-Value Paaren.
	Die Konvention muss 'Key = Value' entsprechen.

	@param file Pfad zur Datei.
	@return map Key-Value Paare der Datei.
	*/
	static std::map<std::string, std::string> read(std::string file);
};

template<typename K, typename V>
inline void FileFactory::write(std::string file, std::map<K, V> map, const char mode)
{
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		std::ostringstream keyStream;
		std::ostringstream valueStream;

		keyStream << it->first;
		std::string key = keyStream.str();

		valueStream << it->second;
		std::string value = valueStream.str();

		writeLine(file, key + " = " + value + "\n", mode);
	}
}
