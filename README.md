# Chương trình luyện gõ tiếng Anh với vài các chủ đề

> Mỗi khi trả lời thư thì chúng ta có thể từ từ viết và
kiểm soát lỗi chính tả khi chúng ta viết nhưng khi làm việc
trực tiếp việc gõ có thể sẽ làm chúng ta bị lỗi chính tả
hoặc sai sót, hôm nay rảnh rỗi tự tạo ra một ứng dụng nhằm
mục đích cải thiện vấn đề này.

# Yêu cầu

Hiện tại phiên bản này đang viết trên `Ubuntu 20.04` sử dụng
`g++` phiên bản `9.3.0`, có cài đặt `gtk3+` để thiết kế giao
diện và xử lý sự kiện, có thể nói với hệ điều hành lõi là `Linux`
`g++` yêu cầu từ `4.8+` và có cài đặt `gtk3+` đều có thể biên dịch
và chạy được mã này. Vì vậy yêu cầu tối thiểu như sau

1. `g++` phiên bản `4.8` trở lên
2. `gtk` phiên bản `3.0` trở lên
3. `Make`

# Cài đặt

Bạn có thể tải thông qua `git` và chạy bằng các lệnh sau

```
git clone https://github.com/hoathienvu8x/Luyen-Go-Chat-Tieng-Anh.git --branch master --single-branch LuyenGoTiengAnh
cd LuyenGoTiengAnh
make
```

Sau khi chạy xong các lệnh nếu như không có lỗi trong quá trình biên dịch thì
sẽ có tập tin `elearn` chúng ta chạy nó bằng lệnh `./elearn` lưu ý trước khi chạy
vui lòng thêm vào tập tin `topics.json` nếu như bạn không chỉnh sửa đường dẫn
của tập tin với nội dung như sau

```JSON
[
    {
        "source":"Hello",
        "destination":"Xin Chào",
        "data":[
            {
                "source":"Hey man.",
                "destination":"Ê anh bạn, hoặc Chào."
            },
            {
                "source":"How's it going? or How are you doing?",
                "destination":"Dạo này bạn thế nào?"
            },
            {
                "source":"What's up?, What's new?, or What's going on?",
                "destination":"Có chuyện gì đó? Có gì mới không? Có chuyện gì vậy ạ?"
            },
            {
                "source":"How's everything ?",
                "destination":"Mọi thứ sao?"
            },
            {
                "source":"How's it going?",
                "destination":"Dạo này bạn thế nào rồi?"
            },
            {
                "source":"Haven't seen you for a long time.",
                "destination":"Lâu rồi không gặp bạn."
            },
            {
                "source":"Nice to meet you.",
                "destination":"Rất vui khi gặp bạn."
            }
        ]
    },
    {
        "source":"Goodbye"
        "destination":"Tạm Biệt",
        "data":[
            {
                "source":"Bye!",
                "destination":"Tạm biệt!"
            },
            {
                "source":"Goodbye!",
                "destination":"Tạm biệt nhé!"
            },
            {
                "source":"Bye for now!",
                "destination":"Tạm biệt nhé!"
            },
            {
                "source":"See you!",
                "destination":"Tạm biệt bạn."
            },
            {
                "source":"Be seeing you!",
                "destination":"Hẹn gặp lại!"
            },
            {
                "source":"See you soon!",
                "destination":"Mong sớm gặp lại bạn!"
            },
            {
                "source":"I'm off.",
                "destination":"Tôi đi đây."
            },
            {
                "source":"Catch you later!",
                "destination":"Gặp lại bạn sau!"
            },
            {
                "source":"Good night!",
                "destination":"Chúc ngủ ngon!"
            },
            {
                "source":"Farewell.",
                "destination":"Tạm biệt!"
            },
            {
                "source":"So long.",
                "destination":"Tạm biệt!"
            },
            {
                "source":"Alright then.",
                "destination":"Tạm biệt!"
            },
            {
                "source":"Have a good one.",
                "destination":"Chúc một ngày tốt lành."
            },
            {
                "source":"See you later.",
                "destination":"Gặp lại bạn sau"
            },
            {
                "source":"Talk to you later."
                "destination":"Nói chuyện với bạn sau nhé!"
            },
            {
                "source":"Later!",
                "destination":"Gặp lại sau!"
            },
            {
                "source":"Smell you later.",
                "destination":"Hẹn gặp lại bạn sau."
            },
            {
                "source":"Peace!",
                "destination":"Tạm biệt!"
            }
        ]
    }
]
```

Kiểu kiểu đại loại rứa :) tiếng anh của mình hơi gà mờ, xưa học khoa toán
theo lĩnh vực toán lý thuyết, đọc hiểu tài liệu tiếng anh thì ok nhưng đi học
lại bị một bà cô bên khoa tiếng anh chửi như đúng rồi dù mình cũng biết dịch
câu của bà chửi, (Mỗi người ai cũng có cái giỏi riêng) tôi không chê bà cô đó
dốt toán nhưng mà cũng nên im lặng, và giờ sau 14 năm ra trường, giờ mới viết
cái phần luyện gõ này, vì nay cũng đã nguôi nguôi giận dữ với cô í ahihi.

> Lưu ý: Bạn có thể thêm vào các câu có ngữ cảnh tốt hơn với những hội thoại
của bạn để tạo sự sinh động và linh hoạt tạo niềm vui cho cả hai bên

Chúc mọi người thành công.

_(Hãy dùng tiếng Anh để tiếp cận thông tin - hạn chế dùng tiếng anh để lòe người khác)_
