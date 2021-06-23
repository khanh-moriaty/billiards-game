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

- [Hướng dẫn cài đặt](#hướng-dẫn-cài-đặt)
    * [Cài đặt cho hệ điều hành Windows](#cài-đặt-cho-hệ-điều-hành-windows)
    * [Cài đặt cho các hệ điều hành Linux](#cài-đặt-cho-các-hệ-điều-hành-linux)
- [Hướng dẫn điều khiển](#hướng-dẫn-điều-khiển)
- [Luật chơi](#luật-chơi)
- [Mô phỏng trạng thái game](#mô-phỏng-trạng-thái-game)

---

<!-- ## Yêu cầu kỹ thuật

Hiện tại chương trình của chúng tôi chỉ mới hỗ trợ cho nền tảng Microsoft Windows. Trước khi đến với bước cài đặt, vui lòng kiểm tra hệ thống của bạn đã có sẵn những tiện ích sau:

- Windows 32-bit hoặc 64-bit.
- Trình biên dịch GNU dành cho Windows: MinGW, MinGW-w64, hoặc TDM-GCC.
- GCC >= 5.1.0. -->

## Hướng dẫn cài đặt

### Cài đặt cho hệ điều hành Windows

**Yêu cầu kỹ thuật:**
- Windows 32-bit hoặc 640bit.
- Trình biên dịch GNU dành cho Windows: MinGW, MinGW-w64, hoặc TDM-GCC.
- GCC >= 5.1.0.
- OpenGL >= 3.3.
- Python3 + pip.

**Tiến hành cài đặt:**

*Đối với người dùng cuối:* Để thực hiện quy trình cài đặt hoàn chỉnh, thực thi lệnh `make install`. Sau khi thực thi thành công, tệp tin trò chơi `BilliardsGame.exe` sẽ được tạo.

*Đối với các nhà phát triển:* Để giữ lại các tệp tin mã máy sau khi biên dịch, sử dụng lệnh `make`.

Ngoài ra, nhằm tăng tính tiện dụng cho quá trình phát triển và kiểm thử chương trình, có thể thực hiện lệnh `make run` để biên dịch và lập tức khởi động trò chơi.

Sau khi hoàn tất việc lập trình và kiểm thử mã nguồn, thực hiện lệnh `make clean` để dọn dẹp những tệp tin không cần thiết.

**Khởi động Billiards Server**

Cài đặt các thư viện Python cần thiết thông qua lệnh `pip`:

```
pip install -r requirements.txt
```

Khởi động Billiards Server bằng lệnh: `python3 cv/main_cv.py`.

### Cài đặt cho các hệ điều hành Linux

**Sử dụng Docker Image có sẵn:** TBA.

**Tự xây dựng Docker Image:**

Để xây dựng lại Docker Image, di chuyển đến thư mục chứa chương trình và thực hiện lệnh sau:

```shellscript
docker build -t billiards-game:latest .
```

**Khởi động trò chơi:**

Lần đầu khởi động trò chơi, bạn sẽ cần tạo Docker Container cho Image vừa xây dựng. Để tạo Docker Container, thực hiện lệnh sau:

```shellscript
docker run -it --name billiards-game --device=/dev/dri -v $XAUTHORITY:/root/.Xauthority --network="host" -e DISPLAY=$DISPLAY billiards-game:latest
```

Sau khi thực hiện thành công câu lệnh bên trên, giao diện của trò chơi sẽ được hiển thị lên màn hình.

Nếu những lần sau muốn khởi động trò chơi, bạn chỉ cần thực hiện lệnh sau:

```shellscript
docker start -i billiards-game
```


## Hướng dẫn điều khiển

TBD

## Luật chơi

TBD

## Mô phỏng trạng thái game

TBD
