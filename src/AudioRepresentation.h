/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file AudioRepresentation.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_AUDIOREPRESENTATION_H
#define TAL_TO_GROEP_AUDIOREPRESENTATION_H
#include <string>
#include <vector>
#include <ostream>

/**
 * Genres in which the library has been divided
 */
enum MusicGenres{
    Classical, /** << */
    ClassicalRock, /** << */
    Dance, /** << */
    Focus, /** << */
    ModernRock, /** << */
    Pop, /** << */
    MovieMusic /** << */
};

/**
 * @class AudioRepresentation
 * @brief Intermediary class between the library and the rest of the application.
 * Class instances are used to write to the library, reading is performed with static member functions.
 */
class AudioRepresentation {
public:
    /**
     * @brief Default constructor for an audio representation
     */
    AudioRepresentation()=default;
    /**
     * @brief Constructor, initialises the title and initialises a file in the library.
     * Use this only if you want to create a new file.
     *
     * @param path The path of the audio file to write into the library.
     * @param genre The genre to write in.
     * @param isTitle Whether or not path should be handled as an already formatted title.
     */
    AudioRepresentation(const std::string& path, enum MusicGenres genre, bool isTitle=false);


    /**
     * @brief Adds data to this object in the library (../library/).
     *
     * @param data  Data that will be added
     */
    void addData(const std::string& data);

    /**
     * @brief Opening an audio representation file if it exists in the library.
     * This can be used of the previous object was destroyed and data still needs to be written to the file.
     *
     * @param title   title of the file that already exists
     */
    void open(const std::string& title);

    /**
     * @brief Opens an output stream to the library file associated with the information provided.
     * @warning The calling function has the responsibility to close the stream when it is finished writing to it.
     * @warning The calling function has the responsibility to de-allocate the memory of the stream when it is finished working with it.
     *
     * @return Pointer to the output stream generated.
     */
    std::ofstream * getOstream();
    /**
     * @brief Opens an input stream to the library file associated with the information provided.
     * @warning The calling function has the responsibility to close the stream when it is finished writing to it.
     * @warning The calling function has the responsibility to de-allocate the memory of the stream when it is finished working with it.
     *
     * @return Pointer to the input stream generated.
     */
    static std::ifstream * getSongDataStream(const std::string &fileName);



protected:

    /**
     * @brief Adds this object to the library (../library/).
     * Writes only the title. This function can be used if the data part is too large to write at once.
     */
    void addTitleToLibrary();

private:
    std::string _title;
    enum MusicGenres _genre;
};


#endif //TAL_TO_GROEP_AUDIOREPRESENTATION_H
