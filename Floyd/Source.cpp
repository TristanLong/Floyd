#include "iostream"
#include "fstream"
using namespace std;

const int MAX = 20;

struct maTrix {
	int maTranKe[MAX][MAX];
	int soDinh;
};

void readFile(maTrix& mtk) {
	ifstream inFile("Text.txt");
	if (!inFile.is_open()) {
		cout << "\nKhong the mo tep";
		return;
	}

	inFile >> mtk.soDinh;
	for (int i = 0; i < mtk.soDinh; i++) {
		for (int j = 0; j < mtk.soDinh; j++) {
			inFile >> mtk.maTranKe[i][j];
		}
	}
	inFile.close();
}

void outputMaTrix(int matrix[MAX][MAX], int soDinh) {
	cout << "\nMA TRAN KE: " << endl;
	for (int i = 0; i < soDinh; i++) {
		for (int j = 0; j < soDinh; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void Floyd(maTrix graph) {
	int khoangCachNganNhat[MAX][MAX]; // Ma trận để lưu trữ khoảng cách ngắn nhất giữa mọi cặp đỉnh
	int dinhTrungGian[MAX][MAX]; // Ma trận để lưu trữ đỉnh trung gian

	// Khởi tạo ma trận khoảng cách ngắn nhất và ma trận đỉnh trung gian ban đầu
	for (int i = 0; i < graph.soDinh; i++) {
		for (int j = 0; j < graph.soDinh; j++) {
			khoangCachNganNhat[i][j] = graph.maTranKe[i][j];

			if (khoangCachNganNhat[i][j] != 0 && i != j)
				dinhTrungGian[i][j] = i;
			else
				dinhTrungGian[i][j] = -1;
		}
	}

	// Thuật toán Floyd-Warshall
	for (int k = 0; k < graph.soDinh; k++) {
		for (int i = 0; i < graph.soDinh; i++) {
			for (int j = 0; j < graph.soDinh; j++) {
				if (khoangCachNganNhat[i][j] > khoangCachNganNhat[i][k] + khoangCachNganNhat[k][j]) {
					khoangCachNganNhat[i][j] = khoangCachNganNhat[i][k] + khoangCachNganNhat[k][j];
					dinhTrungGian[i][j] = dinhTrungGian[k][j]; // Cập nhật đỉnh trung gian
				}
			}
		}
	}

	// In ra ma trận khoảng cách ngắn nhất
	cout << "Ma tran khoang cach ngan nhat:" << endl;
	outputMaTrix(khoangCachNganNhat, graph.soDinh);

	// In ra ma trận đỉnh trung gian
	cout << "Ma tran dinh trung gian:" << endl;
	outputMaTrix(dinhTrungGian, graph.soDinh);
}
int main() {
	maTrix graph;
	readFile(graph);
	Floyd(graph);
 }
