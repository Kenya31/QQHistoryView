#include "QQHistory.h"

QQHistory::QQHistory(void)
{
	// �R���X�g���N�^
	//cout << "QQHistory()���Ă΂�܂����B" << endl;
	SetZthumbnail((void *)0);
	SetThumbnailSize(0);
	SetThumbFileName("");
}


QQHistory::~QQHistory(void)
{
	// �f�X�g���N�^
	//cout << "~QQHistory()���Ă΂�܂����B" << endl;
}

void QQHistory::SetZthumbnail(void *value)
{
	// zThumbnail�̃Z�b�^�[
	this->zThumbnail = value;
}


void * QQHistory::GetZthumbnail(void)
{
	// zThumbnail�̃Q�b�^�[
	return this->zThumbnail;
}

void QQHistory::SetThumbnailSize(int value)
{
	// zThumbnail�̃Z�b�^�[
	this->thumbSize = value;
}


int QQHistory::GetThumbnailSize(void)
{
	// zThumbnail�̃Q�b�^�[
	return this->thumbSize;
}

void QQHistory::SetThumbFileName(string value)
{
	// fileName�̃Z�b�^�[
	this->thumbFileName = value;
}


string QQHistory::GetThumbFileName(void)
{
	// fileName�̃Q�b�^�[
	return this->thumbFileName;
}
