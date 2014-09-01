#include "QQHistory.h"

QQHistory::QQHistory(void)
{
	// コンストラクタ
	//cout << "QQHistory()が呼ばれました。" << endl;
	SetZthumbnail((void *)0);
	SetThumbnailSize(0);
	SetThumbFileName("");
}


QQHistory::~QQHistory(void)
{
	// デストラクタ
	//cout << "~QQHistory()が呼ばれました。" << endl;
}

void QQHistory::SetZthumbnail(void *value)
{
	// zThumbnailのセッター
	this->zThumbnail = value;
}


void * QQHistory::GetZthumbnail(void)
{
	// zThumbnailのゲッター
	return this->zThumbnail;
}

void QQHistory::SetThumbnailSize(int value)
{
	// zThumbnailのセッター
	this->thumbSize = value;
}


int QQHistory::GetThumbnailSize(void)
{
	// zThumbnailのゲッター
	return this->thumbSize;
}

void QQHistory::SetThumbFileName(string value)
{
	// fileNameのセッター
	this->thumbFileName = value;
}


string QQHistory::GetThumbFileName(void)
{
	// fileNameのゲッター
	return this->thumbFileName;
}
