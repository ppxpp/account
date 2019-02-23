# 常用密码哈希算法

## PBKDF2算法
[PBKDF2](https://en.wikipedia.org/wiki/PBKDF2#cite_note-5)(Password-Based Key Derivation Function 2)算法的基本原理是通过指定的伪随机函数（pseudorandom function），将输入的密码和盐值进行反复运算，最终计算出一个密钥。 通过将迭代的重复次数设定得足够高，使得暴利破解的难度变得非常大。 在工程实践中，`PRF`可以采用`HMAC-SHA256`、`HMAC-SHA512`等算法实现。

PBKDF2算法包含5个参数：
```
DK = PBKEF2(PRF, Password, Salt, c, dkLen)
```
其中：
* `PRF`为伪随机函数，输入2两个参数，并输出一个长度为`hLen`的结果
* `Password`为账号密码
* `Salt`为添加的盐值，长度推荐不小于64bits
* `c`为迭代的次数，推荐不小于100 000次
* `dkLen`是最终得到的密钥的长度，单位为bit
* `DK`为最终输出的密钥

DK按照如下格式组成：
```
DK = T1 || T2 || ... || Tdklen/hlen
```
其中，
```
Ti = F(Password, Salt, c, i)
```
函数`F`是对每次迭代出的结果进行异或操作，即：
```
F(Password, Salt, c, i) = U1 ^ U2 ^ ... ^ Uc
```
其中，
```
U1 = PRF(Password, Salt || INT_32_BE(i))
U2 = PRF(Password, U1)
...
Uc = PRF(Password, Uc-1)
```

## bcrypt算法
[bcrypt](https://en.wikipedia.org/wiki/Bcrypt#Algorithm)算法会生成一个盐值，并将盐值混入在计算出的hash串中，在验证密码时，也无需单独提供盐值。
加密后的密钥格式一般为：
```
$2a$10$/bTVvqqlH9UiE0ZJZ7N2Me3RIgUCdgMheyTgV0B4cMCSokPa.6oCa
```
其中：$是分割符，2a是bcrypt加密版本号。10是cost的值，用于控制算法的复杂度。而后的前22位是salt值。剩余字符串就是密码的密文。