#ifndef DWARFFORTRESS_H
#define DWARFFORTRESS_H

#include <QString>
#include <QObject>

/**
 * Utility singleton class that provides access to the various
 * DF data files.
 *
 * It automatically tries to locate a DF installation, first looking
 * in the same directory it is located, and then in various other places.
 */
class DwarfFortress : public QObject
{
    Q_OBJECT
public:
    static DwarfFortress& instance()
    {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        static DwarfFortress instance;
        return instance;
    }

    /**
     * Returns whether a DF installation has been located
     * If this function returns false, then the return value of
     * nearly every other function is undefined.
     */
    bool hasDF() const;

    /**
      * Returns the path to the DF installation
      * @see DwarfFortress::hasDF();
      */
    QString getDFFolder() const;

    /**
     * Set the path to the DF installation
     */
    void setDFFolder(const QString & path);

    /**
     * Returns the full path and file name to d_init.txt
     * @see DwarfFortress::hasDF();
     */
    QString getDInitPath() const;

    /**
     * Returns the full path and file name to init.txt
      * @see DwarfFortress::hasDF();
     */
    QString getInitPath() const;

    /**
     * Returns the full path and file name to interface.txt
     * @see DwarfFortress::hasDF();
     */
    QString getInterfacePath() const;

    /**
     * Returns the full path to the save directory
     * @see DwarfFortress::hasDF();
     */
    QString getSavePath() const;

    /**
      * Returns the full path to the raw objects dir
      */
    QString getRawObjectsPath() const;

    /**
     * Looks through init.txt and d_init.txt for [option:value] and returns value.
     */
    QString getOption(const QString &option) const;
    void setOption(const QString &option, const QString & newValue);

    /**
     * This function searches through the RAWs and returns "YES" if find is found in them,
     * otherwise "NO". It returns a QString instead of a boolean because it can be used more
     * directly in the GUI code this way.
    **/
    QString rawsFind(const QString &find) const;
    void rawsReplace(const QString &old, const QString &replaced);

signals:
    /**
      * Emitted when the DF folder changes
      */
    void dfFolderChanged();


private:
    // this is a singleton, so the ctor is private
    DwarfFortress();

    DwarfFortress(DwarfFortress const&);  // Don't Implement
    void operator=(DwarfFortress const&); // Don't implement

    /**
     * Looks for a DF insallation at a given location
     */
    QString findInstallation(const QString &path, const QString &folder_name = "df_linux");


    QString m_dfFolder;
    bool m_hasDF;
};
#endif // DWARFFORTRESS_H
