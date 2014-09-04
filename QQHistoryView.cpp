/**
* QQHistoryView.exe
*
*/
#include <direct.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "QQHistory.h"

#pragma execution_character_set("UTF-8")

#define DOCTYPE_HTML "<!DOCTYPE html>"
#define HTML_TAG_START "<html>"
#define HTML_TAG_END "</html>"
#define HEAD_TAG_START "<head>"
#define HEAD_TAG_END "</head>"
#define TITLE_TAG_START "<title>"
#define TITLE_TAG_END "</title>"
#define STYLE_TAG_START "<style>"
#define DIV_STYLE "div { white-space:pre; }"
#define STYLE_TAG_END "</style>"
#define BODY_TAG_START "<body>"
#define BODY_TAG_END "</body>"
#define META_TAG "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"
#define BREAK_TAG "<br/>"
#define EMPTY_STRING ""
#define RESULT_DIR "result"
#define IMAGE_THUMBNAIL_DIR "result/image_thumbnail"
#define IMAGE_ORIGINAL_DIR "result/image_original"
#define AUDIO_DIR "result/Audio"
#define MYFOLDER_DIR "result/MyFolder"
#define QQ_HTML "result/QQ.html"

/**
* クエリ結果をHTMLタグで整形して出力
* 一覧形式
*
*/
void PrintResult(vector<QQHistory> records, ofstream *QQ_html) {
	string uin;
	string jst;
	string type;
	string flag;
	string read;
	string content;
	string picUrl;

	// Last uin value.
	string last_uin;

	// 1レコード分のデータを格納するオブジェクト
	QQHistory qh;
	vector<QQHistory>::iterator it = records.begin();

	// 1レコードずつ処理
	while( it != records.end() ) {
		qh = *it;

		// UIN
		uin = qh.GetValue("uin");

		// JST
		jst = qh.GetValue("jst");

		// TYPE
		type = qh.GetValue("type");

		// FLAG
		flag = qh.GetValue("flag");

		// READ
		read = qh.GetValue("read");

		// CONTENT
		content = qh.GetValue("content");

		// picUrl
		picUrl = qh.GetValue("picUrl");

		if (it == records.begin()) {
			// First record.
			*QQ_html << "<table border=\"2\">" << endl;
			*QQ_html << "<th width=\"150\" nowrap>相手のQQ番号</th>" << endl;
			*QQ_html << "<th width=\"150\" nowrap>日時(日本時間)</th>" << endl;
			*QQ_html << "<th nowrap>送受信種別</th>" << endl;
			//*QQ_html << "<th nowrap>未読/既読</th>" << endl;
			*QQ_html << "<th>内容</th>" << endl;
		} else if (last_uin != uin) {
			// Differ last value of uin.
			*QQ_html << "</table>" << endl;
			*QQ_html << "<hr size=\"5\"/>" << endl;
			*QQ_html << "<table border=\"2\">" << endl;
			// Output header
			*QQ_html << "<th width=\"150\" nowrap>相手のQQ番号</th>" << endl;
			*QQ_html << "<th width=\"150\" nowrap>日時(日本時間)</th>" << endl;
			*QQ_html << "<th nowrap>送受信種別</th>" << endl;
			//*QQ_html << "<th nowrap>未読/既読</th>" << endl;
			*QQ_html << "<th>内容</th>" << endl;
		}

		// uinを記録
		last_uin = uin;

		// 出力
		*QQ_html << "<tr>" << endl;
		// QQ number.
		*QQ_html << "<td nowrap>" << uin << "</td>" << endl;
		// Time.
		*QQ_html << "<td nowrap>" << jst << "</td>" << endl;
		// Receive or Send.
		if ("0" == flag) {
			*QQ_html << "<td nowrap align=\"center\">送信</td>" << endl;
		} else if ("1" == flag) {
			*QQ_html << "<td nowrap align=\"center\">受信</td>" << endl;
		} else {
			*QQ_html << "<td nowrap align=\"center\">不明</td>" << endl;
		}
		/*
		// 未読/既読
		if ("0" == read) {
			*QQ_html << "<td nowrap align=\"center\">未読</td>" << endl;
		} else if ("1" == read) {
			*QQ_html << "<td nowrap align=\"center\">既読</td>" << endl;
		} else {
			*QQ_html << "<td nowrap align=\"center\">不明</td>" << endl;
		}
		*/
		// Message
		*QQ_html << "<!-- type=\"" << type << "\" -->" << endl;
		if ("0" == type) {
			// Text message.
			*QQ_html << "<td><div>" << content << "</div></td>" << endl;
		} else if ("1" == type) {
			// Picture data.
			*QQ_html << "<td><div>" << picUrl << "</div></td>" << endl;
		} else if ("2" == type) {
			// ?
		} else if ("3" == type) {
			// Sound data.
			*QQ_html << "<td><div>" << content << "</div></td>" << endl;
		} else if ("4" == type) {
			// Video data.
			*QQ_html << "<td><div>" << content << "</div></td>" << endl;
		} else {
			// Other data.
			*QQ_html << "<td><div>" << content << "</div></td>" << endl;		}
		*QQ_html << "</tr>" << endl;

		// Add iterator.
		it++;

		// Clear parameters.
		uin = EMPTY_STRING;
		jst = EMPTY_STRING;
		type = EMPTY_STRING;
		flag = EMPTY_STRING;
		read = EMPTY_STRING;
		content = EMPTY_STRING;
		picUrl = EMPTY_STRING;
	}
}

/**
* HTMLタグの開始を出力
*/
void PrintHtmlTagStart(ofstream *QQ_html) {
	*QQ_html << DOCTYPE_HTML << endl;
	*QQ_html << HTML_TAG_START << endl;
	*QQ_html << HEAD_TAG_START << endl;
	*QQ_html << META_TAG << endl;
	*QQ_html << TITLE_TAG_START << endl;
	*QQ_html << TITLE_TAG_END << endl;
	*QQ_html << STYLE_TAG_START << endl;
	*QQ_html << DIV_STYLE << endl;
	*QQ_html << STYLE_TAG_END << endl;
	*QQ_html << HEAD_TAG_END << endl;
	*QQ_html << BODY_TAG_START << endl;
	*QQ_html << BREAK_TAG << endl;
}

/**
* HTMLタグの終端を出力
*/
void PrintHtmlTagEnd(ofstream *QQ_html) {
	*QQ_html << HTML_TAG_END << endl;
	*QQ_html << BODY_TAG_END << endl;
}

/**
* Execute query and get name of message tables.
*/
int getQQHistoryTables(sqlite3 *db, vector<string> *tables) {
	int sqlite3_result = 0;
	const unsigned char *value = (unsigned char *)0;
	sqlite3_stmt *stmt = (sqlite3_stmt *)0;

	// Get name message tables excludes 'tb_c2cMsg_1001' and 'tb_c2cMsg_10000'.
	/*
	const char *show_tables = "SELECT name FROM sqlite_master "
		"WHERE type = 'table' AND name LIKE 'tb_c2cMsg_%' "
		"AND name != 'tb_c2cMsg_1001' AND name != 'tb_c2cMsg_10000';";
		*/
	const char *show_tables = "SELECT uin FROM tb_c2cTables"
		" WHERE uin != 'tb_c2cMsg_1001' AND uin != 'tb_c2cMsg_10000'"
		" AND uin != 'tb_c2cMsg_2909288299' AND uin != 'tb_recentC2CMsg'"
		" ORDER BY uin;";

	if ((sqlite3 *)0 == db) {
		// DB file is not open.
		tables = (vector<string> *)0;
	} else {
		// Generate statement.
		sqlite3_prepare(db, show_tables, strlen(show_tables), &stmt, NULL);

		// Clear statement buffer.
		sqlite3_reset(stmt);

		// Execute query.
		while (SQLITE_ROW == (sqlite3_result = sqlite3_step(stmt))) {
			value = sqlite3_column_text(stmt, 0);
			// Add to object array.
			tables->push_back(reinterpret_cast <char const *> (value));
		}
		// stmtを解放
		sqlite3_finalize(stmt);
	}

	return sqlite3_result;
}


/**
*  Execute query and get result set to "results".
*/

int getQQHistoryRecords(sqlite3 *db, string table, vector<QQHistory> *results) {
	int sqlite3_result = 0;
	int columnCount = 0;
	const char *select_sql = "SELECT msgId, uin, DATETIME(time, 'unixepoch', 'localtime') AS jst, type, flag, read, content, picUrl FROM ";
	const char *order_by_sql = " ORDER BY time;";
	const char *param = (char *)0;
	const unsigned char *value = (unsigned char *)0;
	string sql;
	QQHistory qh;


	// Prepared statement.
	sqlite3_stmt *stmt = (sqlite3_stmt *)0;

	if ((sqlite3 *)0 == db) {
		// DB file is not open.
		results = (vector<QQHistory> *)0;
		sqlite3_result = -1;
	} else if (0 == table.length()) {
		// Table name is empty.
		results = (vector<QQHistory> *)0;
		sqlite3_result = -2;
	} else {
		// Prepare sql.
		sql += select_sql;
		sql += table;
		sql += order_by_sql;

		// Generate statement.
		sqlite3_prepare(db, sql.c_str(), strlen(sql.c_str()), &stmt, NULL);

		// Clear statement buffer.
		sqlite3_reset(stmt);

		// Set columns count.
		columnCount = sqlite3_column_count(stmt);

		// Execute query.
		while (SQLITE_ROW == (sqlite3_result = sqlite3_step(stmt))) {
			qh = QQHistory();
			for (int i = 0; i < columnCount ; i++) {
				param = sqlite3_column_name(stmt, i);
				value = sqlite3_column_text(stmt, i);
				if ((unsigned char *)0 == value) {
					qh.SetValue(param, EMPTY_STRING);
				} else {
					// Set to QQHistory class.
					qh.SetValue(param, reinterpret_cast <char const *> (value));
				}
			}
			// Add to object array.
			results->push_back(qh);
		}
		// stmtを解放
		sqlite3_finalize(stmt);
	}

	return sqlite3_result;
}

/**
* main routine.
*
*
*/
int main(int argc, char * argv[])
{
	int result = -1;
	sqlite3 *db = (sqlite3 *)0;
	string table;
	vector<string>::iterator it;
	// テーブル名を格納する配列
	vector<string> tables;
	// クエリ結果を格納する配列
	vector<QQHistory> results;

	// ファイル存在確認のための変数
	struct stat statFile;

	// 出力ファイル
	ofstream QQ_html;

	// Initialize.
	memset(&statFile, 0, sizeof(statFile));

	// 引数をチェック
	if (1 == argc) {
		// 引数が指定されていない
		fprintf(stderr, "Usage: %s <QQ.db>\n", argv[0]);
		exit(-1);
	} else if (0 != stat(argv[1], &statFile)) {
		// ファイルが無い
		fprintf(stderr, "File \"%s\" does not exist.\n", argv[1]);
		exit(-2);
	} else {
		// ファイルが有る
		switch (statFile.st_mode & S_IFMT) {
		case S_IFCHR:
			fprintf(stderr,"File \"%s\" is character device.\n", argv[1]);
			exit(-3);
			break;
		case S_IFDIR:
			fprintf(stderr,"File \"%s\" is directory.\n", argv[1]);
			exit(-4);
			break;
		case S_IFREG:
			//fprintf(stdout,"File \"%s\" is regular file.\n", argv[1]);
			break;
		default:
			fprintf(stderr,"File \"%s\" is unknown.\n", argv[1]);
			exit(-5);
			break;
		}
	}

	// Check output directory.
	if (0 == stat(RESULT_DIR, &statFile)) {
		// "result" exists.
		fprintf(stderr,"Directory \"%s\" exists.\n", RESULT_DIR);
		exit(-6);
	}

	// Open db file.
	result = sqlite3_open(argv[1], &db);

	if (SQLITE_OK != result) {
		fprintf(stderr, "sqlite3_open result[%d]\n", result);
		goto close;
	} else if (SQLITE_DONE != (result = getQQHistoryTables(db, &tables))){
		// Failed to get table name.
		fprintf(stderr, "getQQHistoryTables failed result[%d]\n", result);
	} else {
		it = tables.begin();
		while(it != tables.end()) {
			table = *it;
			if (SQLITE_DONE != (result = getQQHistoryRecords(db, table, &results))) {
				fprintf(stderr, "getQQHistoryRecords failed result[%d] table[%s]\n", result, table.c_str());
				break;
			}
			it++;
		}
		if (SQLITE_DONE == result) {
			// Create output directory.
			if (0 != stat(RESULT_DIR, &statFile)) {
				// resultフォルダが無い
				_mkdir(RESULT_DIR);
			}
			QQ_html.open(QQ_HTML, ios::out|ios::binary|ios::trunc);

			PrintHtmlTagStart(&QQ_html);
			PrintResult(results, &QQ_html);
			PrintHtmlTagEnd(&QQ_html);
			QQ_html.flush();
			QQ_html.close();
		} else { 
			fprintf(stderr, "getQQHistoryRecords failed result[%d]\n", result);
		}
	}

close:
	// DBを閉じる
	sqlite3_close(db);

	return result;
}
