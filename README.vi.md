# Holo Project

### Lưu ý:

> **Đây là phiên bản phát triển (Dev Version).**  
> Holo Project hiện chỉ có tác dụng trưng bày sản phẩm và chưa hoàn thiện.  
> Vui lòng không đánh giá sản phẩm khi nó chưa hoàn thiện.

### Translations:

-   [English](https://github.com/MineHighVN/holo-dev/blob/main/README.md)
-   [Tiếng Việt](https://github.com/MineHighVN/holo-dev/blob/main/README.vi.md)

### Holo Project là gì?

Holo Project cung cấp một cách tiếp cận hoàn toàn mới để xây dựng giao diện người dùng. Với cú pháp quen thuộc như **ReactJS**, Dev có thể dễ dàng viết mã theo mô hình thành phần (component-based), nhưng thay vì sử dụng **WebView**, tất cả đều được hiển thị trực tiếp qua **C++**, mang lại hiệu suất vượt trội.

Điều này không chỉ giúp giảm đáng kể mức tiêu thụ tài nguyên hệ thống mà còn cải thiện tốc độ phản hồi và trải nghiệm người dùng. Các nhà phát triển sẽ không phải lo lắng về việc ứng dụng bị chậm hoặc nặng nề do sự phụ thuộc vào trình duyệt nhúng như trong các framework truyền thống.

-   **C++** được sử dụng để xử lý phần giao diện hiển thị cửa sổ, tận dụng tối đa hiệu suất và khả năng kiểm soát thấp cấp của ngôn ngữ.
-   **Node.js** đảm nhận vai trò điều khiển logic mang lại sự đơn giản và khả năng mở rộng cao với hệ sinh thái phong phú của JavaScript.

Holo Project được thiết kế như một giải pháp thay thế cho các công cụ phát triển ứng dụng desktop nặng nề như **Electron**, giúp giảm thiểu tài nguyên hệ thống mà vẫn giữ được sự linh hoạt và dễ sử dụng.

### Điểm nổi bật:

-   **Hiệu suất cao:** Tận dụng tối đa sức mạnh của C++ cho phần frontend.
-   **Dễ dàng phát triển:** Node.js cung cấp môi trường phát triển đơn giản với nhiều thư viện hỗ trợ.
-   **Nhẹ và hiệu quả:** Ít tài nguyên hơn so với các giải pháp truyền thống, làm cho Holo Project phù hợp với các ứng dụng yêu cầu hiệu suất cao.
-   **Cú pháp quen thuộc:** Nếu bạn đã từng làm việc với ReactJS, bạn sẽ cảm thấy dễ dàng khi sử dụng Holo Project.
-   **Không cần WebView:** Holo Project loại bỏ hoàn toàn WebView, thay thế bằng giao diện render hiệu suất cao thông qua C++.
-   **Tối ưu hóa tài nguyên:** Ứng dụng được tối ưu hóa để hoạt động nhẹ nhàng, tiêu thụ ít RAM và CPU hơn so với các framework khác.
-   **Môi trường hợp nhất:** Kết hợp sức mạnh của **JavaScript** để xử lý logic và **C++** để xây dựng giao diện, tất cả trong một hệ sinh thái đồng bộ.
-   **Mã nguồn mở:** Mọi người có thể tham gia, tùy chỉnh và đóng góp cho dự án.

### Cách sử dụng

Cấu trúc của HoloJS gần như tương tự với React. Hàm \_holo hoạt động giống như \_jsx trong React. Tuy nhiên, do HoloJS chưa sử dụng Babel, mọi người cần viết \_holo với cấu trúc sau:

> HTML

```html
<p>Hello world from @holo/dev</p>
```

> HoloJS

```js
_holo("p", {
    children: "Hello world from @holo/dev",
});
```

Khi viết đầy đủ, đoạn mã sẽ trông như sau:

```js
const { _holo, holo } = require("@holo/dev");

const App = () => {
    holo.window.setTitle("Holo Project (@holo/dev)");

    return _holo("p", {
        children: `Hello world from @holo/dev`,
    });
};

module.exports = App;
```

### Cách cài đặt

Hiện tại, Holo Project mới chỉ được thử nghiệm trên môi trường Linux (Kubuntu 24.04.1 LTS x86_64) có thể sẽ xảy ra lỗi ở phiên bản windows

Để cài đặt Holo Project, bạn cần thực hiện các bước sau:

1. Clone từ repository của holo-dev

```bash
git clone https://github.com/MineHighVN/holo-dev
cd holo-dev
```

2. Tải các thư viện cần thiết

```bash
npm install
```

3. Cài đặt GLFW

```bash
sudo apt install libglfw3-dev
```

3. Chạy ứng dụng dưới môi trường dev

```bash
npm run dev
```

Nó sẽ mất một thời gian để khởi chạy trong lần đầu tiên vì có thể nó sẽ phải build những thư viện cần thiết của C++ cho NodeJS
