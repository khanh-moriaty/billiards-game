<h1><p align="center">MÔ PHỎNG TRẠNG THÁI GAME BILLIARDS</p></h1>

## Giới thiệu

Nhóm của chúng tôi bao gồm ba thành viên:

<img align="right" height="140" src="https://media1.tenor.com/images/f181464c1be3f16db829c46966eab6fd/tenor.gif?itemid=3452012">

|             | Họ và Tên              | MSSV     |
|-------------|------------------------|----------|
| Trưởng nhóm | Hồ Chung Đức Khánh     | 19520624 |
| Thành viên  | Nguyễn Thị Minh Phương | 19522065 |
| Thành viên  | Võ Minh Hiếu           | 19520084 |

<br>

Dưới đây là đồ án môn học CS105.L21.KHTN (Đồ họa Máy tính) và CS231.L21.KHTN (Nhập môn Thị giác Máy tính). Đồ án này bao gồm hai nội dung chính:

<ol>
    <li> Trò chơi Billiards lỗ (8-ball) cho phép người dùng tương tác và điều khiển.
    <li> Tái hiện lại trạng thái của một ván Billiards bất kỳ thông qua một bức ảnh đầu vào.
</ol>

## Mục lục

1. [Yêu cầu kỹ thuật](#yêu-cầu-kỹ-thuật)
2. [Hướng dẫn cài đặt](#hướng-dẫn-cài-đặt)
3. [Hướng dẫn điều khiển](#hướng-dẫn-điều-khiển)
4. [Luật chơi](#luật-chơi)
5. [Mô phỏng trạng thái game](#mô-phỏng-trạng-thái-game)

## Yêu cầu kỹ thuật

Hiện tại chương trình của chúng tôi chỉ mới hỗ trợ cho nền tảng Microsoft Windows. Trước khi đến với bước cài đặt, vui lòng kiểm tra hệ thống của bạn đã có sẵn những tiện ích sau:

- Windows 32-bit hoặc 64-bit.
- Trình biên dịch GNU dành cho Windows: MinGW, MinGW-w64, hoặc TDM-GCC.
- GCC >= 5.1.0.

## Hướng dẫn cài đặt

### Đối với người dùng cuối

Để tiến hành cài đặt chương trình, nhấn tổ hợp phím `Windows + R`, gõ `cmd` để mở cửa sổ dòng lệnh. Kế tiếp, di chuyển đến thư mục chứa mã nguồn chương trình và thực hiện câu lệnh sau:
```
make install
```

Sau khi thực thi thành công câu lệnh trên, thư mục chứa chương trình sẽ phát sinh một tệp tin trò chơi: `BilliardsGame.exe`.

### Đối với nhà phát triển

Nếu bạn là nhà phát triển, để giữ lại các tệp tin mã máy sau khi biên dịch, sử dụng lệnh
```
make
```
Ngoài ra, để tăng tính tiện dụng khi lập trình và kiểm thử, có thể dùng lệnh sau để biên dịch và khởi động trò chơi:
```
make run
```
Sau khi hoàn tất việc lập trình và kiểm thử cho mã nguồn, có thể dọn dẹp những tệp tin không cần thiết thông qua lệnh
```
make clean
```


## Hướng dẫn điều khiển

TBD

## Luật chơi

TBD

## Mô phỏng trạng thái game

TBD