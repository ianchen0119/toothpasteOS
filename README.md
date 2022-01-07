# 牙膏 OS

牙膏 OS 是一個以 mini-riscv-os 為基礎擴充的迷你作業系統。

![](https://i.imgur.com/E1PvoUH.png)

## Description

我已將先前的更動都整合到 mini-riscv-os 之中，目前最新版本的牙膏 OS 與 mini-riscv-os 有以下差異

- 支援 exec, exit 等系統呼叫
- 添加迷你 Shell，可以讓使用者體驗跟作業系統互動的感覺
- 修改 user space app 的新增方式

系統相關實作可以參考 `\docs`，裡面目前記載了除最新更動以外的實作過程與方法。

## Future work

- Impl fork, kill syscalls
- replace the tiny shell with unix-like shell

## Reference

- [mini-riscv-os](https://github.com/cccriscv/mini-riscv-os)
- [xv6](https://github.com/mit-pdos/xv6-public)
- [virtio](https://docs.oasis-open.org/virtio/virtio/v1.1/virtio-v1.1.html)
