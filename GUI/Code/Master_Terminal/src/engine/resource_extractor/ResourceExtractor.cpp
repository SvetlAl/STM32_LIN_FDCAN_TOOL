#include "ResourceExtractor.h"

const QString &ResourceExtractor::target_filename() const
{
    return m_target_filename;
}

void ResourceExtractor::setTarget_filename(const QString &newTarget_filename)
{
    resetOp_result();
    m_target_filename = newTarget_filename;
    QFile targetFile(m_target_filename);
    if (!targetFile.exists()){
        appendOp_result(sts_target_file_not_found);
    }
    if (!targetFile.open(QIODevice::ReadWrite)){
        appendOp_result(sts_target_file_failed_to_open);
        return;
    }
    else{
        QFileInfo fileInfo(targetFile);
        QString absolutePath = fileInfo.absoluteFilePath();
        appendOp_result(absolutePath);
    }
    targetFile.close();

    appendOp_result(sts_target_filename_set + m_target_filename);
    emit target_filename_changed();
}

const QString &ResourceExtractor::replacement_filename() const
{
    return m_replacement_filename;
}

void ResourceExtractor::setReplacement_filename(const QString &newReplacement_filename)
{
    resetOp_result();
    m_replacement_filename = newReplacement_filename;

    QFile replacementFile(m_replacement_filename);
    if (!replacementFile.exists()){
        appendOp_result(sts_replacement_file_non_exist);
    }
    if (!replacementFile.open(QIODevice::ReadWrite)){
        appendOp_result(sts_replacement_file_fail_to_read);
        return;
    }
    else{
        QFileInfo fileInfo(replacementFile);
        QString absolutePath = fileInfo.absoluteFilePath();
        appendOp_result(absolutePath);
    }
    replacementFile.close();

    appendOp_result(sts_replacement_filename_set + m_target_filename);
    emit replacement_filename_changed();
}

const QString &ResourceExtractor::op_result() const
{
    return m_op_result;
}

void ResourceExtractor::setOp_result(const QString &newOp_result)
{
    m_op_result = newOp_result;
    emit operation_result_changed();
}

void ResourceExtractor::appendOp_result(const QString &newOp_result){
   setOp_result(op_result() + "\n" + newOp_result);
}
void ResourceExtractor::resetOp_result(){
    setOp_result("");
}

const QString &ResourceExtractor::output_folder() const
{
    return m_output_folder;
}

void ResourceExtractor::setOutput_folder(const QString &newOutput_folder)
{

    m_output_folder = newOutput_folder;
    resetOp_result();
    appendOp_result(sts_output_dir_set);
    emit output_folder_changed();
}
