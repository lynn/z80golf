#include "Z80.h"
#include <stdio.h>
#include <stdlib.h>


#define	MAX_MEMORY			(32 * 1024)		/* 使えるメモリ */


#ifndef NULL
#define	NULL		(0)
#endif
#ifndef	FALSE
#define	FALSE		(0)
#define	TRUE		(1)
#endif

/// ファイルの読み込み
void* load(const char* fn, int* psize) {
	void* data = NULL;
	FILE* fp = fopen(fn, "rb");
	if (fp != NULL) {
		int size;
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		data = malloc(size);
		if (data != NULL) {
			fread(data, 1, size, fp);
			if (psize != NULL) {
				*psize = size;
			}
		}

		fclose(fp);
	}
	return data;
}

/// 読み込んだデータの解放
void release_load_data(void* data) {
	free(data);
}

//=============================================================================
/// Z80 エミュのドライブ

                               /* Bits in Z80 F register:    */
#define S_FLAG      0x80       /* 1: Result negative         */
#define Z_FLAG      0x40       /* 1: Result is zero          */
#define H_FLAG      0x10       /* 1: Halfcarry/Halfborrow    */
#define P_FLAG      0x04       /* 1: Result is even          */
#define V_FLAG      0x04       /* 1: Overflow occured        */
#define N_FLAG      0x02       /* 1: Subtraction occured     */
#define C_FLAG      0x01       /* 1: Carry/Borrow occured    */

#define M_RET R->PC.B.l=RdZ80(R->SP.W++);R->PC.B.h=RdZ80(R->SP.W++)

/// エミュレータ
Z80 z80;

/// メモリ空間
byte mem[64 * 1024];

/// メモリから１バイト読み込み
byte RdZ80(word A) {
	return mem[A];
}

/// メモリに書き込み
void WrZ80(word Addr, byte Value) {
	mem[Addr] = Value;
}

/// I/O 出力
void OutZ80(word Port, byte Value) {
}

/// I/O 入力
byte InZ80(word Port) {
	return 0;
}

void PatchZ80(register Z80 *R)		{ }
word LoopZ80(register Z80 *R)		{ return INT_QUIT; }



/// 初期化
void init() {
	ResetZ80(&z80);
}

/// メモリへの転送
void trans(word adr, const void* data, int size) {
	const char* tbl = (const char*)data;
	int i;
	if (size >= MAX_MEMORY) {
		size = MAX_MEMORY;
	}
	for (i=0; i<size; ++i) {
		WrZ80(adr+i, tbl[i]);
	}
}

/// 停止済み？
int is_halt() {
	return z80.IFF & IFF_HALT;
}


//=============================================================================

/// リターン処理
void ret() {
	Z80* R = &z80;
	M_RET;
}

/// １文字出力
void _putchar() {
	int c = z80.AF.B.h;
	putchar(c);
	ret();
}

/// １文字入力
void _getchar() {
	int c = getchar();
	if (c != EOF) {
		z80.AF.B.h = c;
		z80.AF.B.l &= ~C_FLAG;
	} else {
		z80.AF.B.l |= C_FLAG;
	}
	ret();
}

/// 特別アドレス関数テーブル
struct {
	word adr;
	void (*func)();
} static const functbl[] = {
	{	0x8000,		_putchar,	},
	{	0x8003,		_getchar,	},
};

/// １命令実行
void step() {
	ExecZ80(&z80);

		// システムコールされた場合、その処理へ飛ばす
	{
		const int N = sizeof(functbl)/sizeof(*functbl);
		int i;
		for (i=0; i<N; ++i) {
			if (z80.PC.W == functbl[i].adr) {
				(*functbl[i].func)();
				break;
			}
		}
	}
}


//=============================================================================

void exec_loop(int maxstep) {
	int i;
	for (i=0; maxstep == 0 || i < maxstep; ++i) {
		if (is_halt())	break;
		step();
	}
}

/// ファイル実行
int exec(const char* fn, int maxstep) {
	int size;
	void* data = load(fn, &size);
	if (data == NULL) {
		fprintf(stderr, "%s: load err\n", fn);
		return FALSE;
	}

	trans(0x0000, data, size);
	release_load_data(data);

	exec_loop(maxstep);

	if (!is_halt()) {
		fprintf(stderr, "time out!\n");
		return FALSE;
	}

	return TRUE;
}


void usage()
{
	fprintf(stdout,
		"usage: [option] z80-source-file\n"
		"option:\n"
		"	-h          help\n"
		"	-s<step>    set max step num\n"
	);
}

const int ERR = 1;

/// エントリ
int main(int argc, char* argv[])
{
	int maxstep = 0;
	int i;

	for (i=1; i<argc; ++i) {
		const char* p = argv[i];
		if (*p != '-')	break;
		switch (p[1]) {
		default:
			fprintf(stderr, "%c: illegal option\n", p[1]);
			return ERR;
		case 'h':
			usage();
			break;
		case 's':
			maxstep = atoi(p + 2);
			break;
		}
	}

	if (i >= argc) {
		usage();
		return ERR;
	}

	if (!exec(argv[i], maxstep)) {
		return ERR;
	}

	return 0;
}

