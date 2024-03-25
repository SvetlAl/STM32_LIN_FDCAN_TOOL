#ifndef PNG_EXTRACTOR_H
#define PNG_EXTRACTOR_H

#include "ResourceExtractor.h"

class PngExtractor : public ResourceExtractor{
Q_OBJECT
    Q_PROPERTY(QString operation_result READ op_result WRITE setOp_result NOTIFY operation_result_changed)
    Q_PROPERTY(QString target_filename READ target_filename WRITE setTarget_filename NOTIFY target_filename_changed)
    Q_PROPERTY(QString replacement_filename READ replacement_filename WRITE setReplacement_filename NOTIFY replacement_filename_changed)
    Q_PROPERTY(QString output_folder READ output_folder WRITE setOutput_folder NOTIFY output_folder_changed)


public:
    PngExtractor(QObject *parent = nullptr): ResourceExtractor(parent){
        setTarget_filename("test_target.exe");
        setOutput_folder("test");

        begin_chars = QByteArrayLiteral("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A");
        end_chars = QByteArrayLiteral("\x00\x00\x00\x00\x49\x45\x4e\x44\xae\x42\x60\x82");
        extn = ".png";

    };
    ~PngExtractor(){
    };

    Q_INVOKABLE void comp_test(){
        QFile targetFile_A(m_target_filename);
        if (!targetFile_A.exists()){
            appendOp_result(sts_target_file_not_found);
            return;
        }

        if (!targetFile_A.open(QIODevice::ReadWrite)){
            appendOp_result(sts_target_file_failed_to_open);
            return;
        }


        QFile targetFile_B(m_output_folder);
        if (!targetFile_B.exists()){
            appendOp_result(sts_target_file_not_found);
            return;
        }

        if (!targetFile_B.open(QIODevice::ReadWrite)){
            appendOp_result(sts_target_file_failed_to_open);
            return;
        }

        QByteArray dataA = targetFile_A.readAll();
        targetFile_A.close();
        QByteArray dataB = targetFile_B.readAll();
        targetFile_B.close();

        int entryNumber = 0;
        int beginIndex = 0;
        int endIndex = 0;

        size_t data_size = dataA.size();
        for(size_t i = 30; i < (data_size-1); i++){
            if((dataB[i-1] != 0x00)) continue;
            size_t pos = i;
            size_t nextpos = i +1;
            if(dataA[pos] == 0x00 && dataA[nextpos] == 0x00){
                if (dataB[pos] != 0x00 || dataB[nextpos] != 0x00) {
                    qDebug() << "mismatchA " << pos << "  " << dataA.at(pos) << "  " << dataA.at(nextpos)<< "  " << dataB.at(i) << "  " << dataB.at(nextpos);
                    return;
                }
            }

        }

        for(size_t i = 30; i < (data_size-1); i++){
            if((dataB[i-1] != 0x00)) continue;
            size_t pos = i;
            size_t nextpos = i +1;
            if(dataB.at(pos) == 0x00 && dataB[nextpos] == 0x00){
                if (dataA[pos] != 0x00 || dataA[nextpos] != 0x00){
                        qDebug() << "mismatchB " << pos;
                        return;
                }
            }


        }









    }



private:


};


#endif // PNG_EXTRACTOR_H
