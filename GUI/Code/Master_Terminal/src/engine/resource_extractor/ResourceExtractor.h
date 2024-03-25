#ifndef RESOURCE_EXTRACTOR_H
#define RESOURCE_EXTRACTOR_H

/***********************************************************************
 *
 *
 * Resource Extractor
 *
 *
 *
 ************************************************************************/

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <QFile>
#include <QDir>

class ResourceExtractor: public QObject{
Q_OBJECT
public:
    ResourceExtractor(QObject * parent = nullptr): QObject(parent){
    };
    ~ResourceExtractor(){
    };

    const QString sts_extracting_data = "Extracting data...";
    const QString sts_target_file_not_found = "Target file not found.";
    const QString sts_target_file_failed_to_open = "Failed to open the target file.";
    const QString sts_no_entries_found = "No entries found.";
    const QString sts_failed_to_create = "Failed to create an output file.";
    const QString sts_extraction_completed = "Extraction completed.";
    const QString sts_failed_to_create_dir = "Failed to create an output dir.";
    const QString sts_target_filename_set = "Target filename: ";
    const QString sts_replacement_filename_set = "Replacement filename: ";
    const QString sts_output_dir_set = "Output dir: ";
    const QString sts_replacement_start = "Replacing...";
    const QString sts_replacement_file_non_exist = "Replacement file doesn't exist.";
    const QString sts_replacement_file_fail_to_read = "Failed to read the replacement file.";
    const QString sts_replacement_file_invalid_format = "Invalid replacement file format.";
    const QString sts_entry_number_not_found = "Replacement entry number not found.";
    const QString sts_failed_to_write_target = "Failed to write the target file.";
    const QString sts_replacement_successful = "Replacement successful.";
    const QString sts_replacement_length_mismatch = "Replacement data length mismatch.";


    Q_INVOKABLE void extract_all(){
        setOp_result(sts_extracting_data);
        QFile file(m_target_filename);
        if (!file.exists()){
            appendOp_result(sts_target_file_not_found);
            return;
        }

        if (!file.open(QIODevice::ReadOnly)){
            appendOp_result(sts_target_file_failed_to_open);
            return;
        }

        QByteArray data = file.readAll();
        file.close();

        int entryNumber = 0;
        int beginIndex = 0;
        int endIndex = 0;

        QDir outputDir(m_output_folder);
        if (!outputDir.exists()){
            if (!outputDir.mkpath(".")){
                appendOp_result(sts_failed_to_create_dir);
                return;
            }
        }

        while ((beginIndex = data.indexOf(begin_chars, endIndex)) != -1){
            endIndex = data.indexOf(end_chars, beginIndex);
            if (endIndex == -1){
                appendOp_result(sts_no_entries_found);
                return;
            }

            QByteArray entryData = data.mid(beginIndex, endIndex - beginIndex + end_chars.length());
            QString fileName = m_output_folder + "/" + QString::number(entryNumber) + extn;

            QFile outputFile(fileName);
            if (!outputFile.open(QIODevice::WriteOnly)){
                appendOp_result(sts_failed_to_create);
                return;
            }

            outputFile.write(entryData);
            outputFile.close();

            entryNumber++;
        }

        appendOp_result(sts_extraction_completed + "  " + QString::number(entryNumber+1) + "  found.");
    }




    Q_INVOKABLE void make_replacement(size_t entry_num){
        setOp_result(sts_replacement_start);
        QFile targetFile(m_target_filename);
        if (!targetFile.exists()){
            appendOp_result(sts_target_file_not_found);
            return;
        }

        if (!targetFile.open(QIODevice::ReadWrite)){
            appendOp_result(sts_target_file_failed_to_open);
            return;
        }

        QByteArray targetData = targetFile.readAll();
        targetFile.close();

        int entryNumber = 0;
        int beginIndex = 0;
        int endIndex = 0;

        while ((beginIndex = targetData.indexOf(begin_chars, endIndex)) != -1){
            endIndex = targetData.indexOf(end_chars, beginIndex);
            if (endIndex == -1){
                appendOp_result(sts_no_entries_found);
                return;
            }

            if (entryNumber == entry_num){
                QFile replacementFile(m_replacement_filename);
                if (!replacementFile.exists()){
                    appendOp_result(sts_replacement_file_non_exist);
                    return;
                }

                if (!replacementFile.open(QIODevice::ReadOnly)){
                    appendOp_result(sts_replacement_file_fail_to_read);
                    return;
                }

                QByteArray replacementData = replacementFile.readAll();
                replacementFile.close();

                int replacementBegin = replacementData.indexOf(begin_chars);
                int replacementEnd = replacementData.lastIndexOf(end_chars);

                if (replacementBegin == -1 || replacementEnd == -1){
                    appendOp_result(sts_replacement_file_invalid_format);
                    return;
                }

                if (endIndex - beginIndex + end_chars.length() != replacementEnd - replacementBegin + end_chars.length()){
                    appendOp_result(sts_replacement_length_mismatch);
                    return;
                }
                targetData.replace(beginIndex, endIndex - beginIndex + end_chars.length(), replacementData.mid(replacementBegin, replacementEnd - replacementBegin + end_chars.length()));
                break;
            }

            entryNumber++;
        }

        if (entryNumber < entry_num){
            appendOp_result(sts_entry_number_not_found);
            return;
        }

        if (!targetFile.open(QIODevice::WriteOnly)){
            appendOp_result(sts_failed_to_write_target);
            return;
        }

        targetFile.write(targetData);
        targetFile.close();

        appendOp_result(sts_replacement_successful);
    }




    const QString &target_filename() const;
    void setTarget_filename(const QString &newTarget_filename);
    const QString &replacement_filename() const;
    void setReplacement_filename(const QString &newReplacement_filename);
    const QString &op_result() const;
    void setOp_result(const QString &newOp_result);
    void appendOp_result(const QString &newOp_result);
    void resetOp_result();

    const QString &output_folder() const;
    void setOutput_folder(const QString &newOutput_folder);

signals:
    void replacement_filename_changed();
    void target_filename_changed();
    void output_folder_changed();
    void operation_result_changed();

protected:
    QString m_target_filename;
    QString m_replacement_filename;
    QString m_output_folder;

    QString m_op_result;

    QByteArray begin_chars = QByteArrayLiteral("\x00\x00\x00");
    QByteArray end_chars = QByteArrayLiteral("\xFF\xFF\xFF");
    QString extn = ".bin";
};

#endif // RESOURCE_EXTRACTOR_H
