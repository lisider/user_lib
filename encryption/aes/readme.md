
```c

aes 是 对称加密算法

加密和解密用到的密钥是相同的，这种加密方式加密速度非常快，适合经常发送数据的场合。缺点是密钥的传输比较麻烦。

```

---


- 加密流程
```c
        密钥
明文 -----------> 密文
        加密函数

注意:
     明文字符长度必须为16的倍数
     密钥字符长度必须为16、24和32
     加密得到的密文字符长度 和 明文字符长度 相同
```


- 解密流程
```c

        密钥
密文 -----------> 明文
        加密函数

```


- 实现

```c

main.c   实现了 16位 密钥 加密 16倍数 明文

```



