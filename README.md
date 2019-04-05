Soal Shift Modul 3
Isnaini Nurul KurniaSari (05111740000010)

Argo Galih Pribadi       (05111740000150)

--Soal 5--
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai 

uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga 

kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. 

Berikut permainan yang Jiwang minta. 

Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.

Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika 

hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada 

monster, tetapi banyak makanan terbatas dan harus beli di Market.

Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai 

angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya 

setiap 20 detik(cooldownnya 20 detik).

Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik 

ketika monster dalam keadaan standby.

Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’

(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain 

akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster 

pemain dengan monster musuh akan menyerang secara bergantian.

Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.

Pembeli (terintegrasi dengan game)

Dapat mengecek stok makanan yang ada di toko.

Jika stok ada, pembeli dapat membeli makanan.

Penjual (terpisah)

Bisa mengecek stok makanan yang ada di toko

Penjual dapat menambah stok makanan.

Spesifikasi program:

Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)

Program terdiri dari 3 scene yaitu standby, battle, dan shop.

Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, 

dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). 

Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode

Health : [health status]

Hunger : [hunger status]

Hygiene : [hygiene status]

Food left : [your food stock]

Bath will be ready in [cooldown]s

Choices

Eat

Bath

Battle

Shop

Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program 

selalu menampilkan 2 menu yaitu serang atau lari. Contoh :


Battle Mode

Monster’s Health : [health status]

Enemy’s Health : [enemy health status]

Choices

Attack

Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program 

selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

        Shop Mode
        Shop food stock : [shop food stock]
        Your food stock : [your food stock]
        Choices
Buy

Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop

Food stock : [shop food stock]

Choices

Restock

Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

``

``
