#include <map>
#include <string>

#include "Record.h"

using namespace std;

/**
 * Inherit Record class.
 */
class QQHistory : public Record
{
public:
	QQHistory(void);
	virtual ~QQHistory(void);

	void QQHistory::SetZthumbnail(void *value);
	void * QQHistory::GetZthumbnail(void);

	void QQHistory::SetThumbnailSize(int value);
	int QQHistory::GetThumbnailSize(void);

	void QQHistory::SetThumbFileName(string value);
	string QQHistory::GetThumbFileName(void);

private:
	void *zThumbnail;
	int thumbSize;
	string thumbFileName;
};
