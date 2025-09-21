# 如何設定 SSH Key 連接多個 Git 倉庫

本文檔將詳細說明如何在本地裝置上設定 SSH key 來連接多個遠端 Git 倉庫。

## 目錄
- [基本概念](#基本概念)
- [生成 SSH Key](#生成-ssh-key)
- [設定多個 SSH Key](#設定多個-ssh-key)
- [設定 SSH Config 檔案](#設定-ssh-config-檔案)
- [測試連接](#測試連接)
- [常見問題](#常見問題)

## 基本概念

SSH Key 是一種安全的身份驗證方式，允許您在不輸入密碼的情況下安全地連接到遠端 Git 倉庫。當您需要連接多個不同的 Git 服務（如 GitHub、GitLab、Bitbucket）或使用不同的帳戶時，設定多個 SSH Key 是必要的。

## 生成 SSH Key

### 1. 檢查現有的 SSH Key

首先檢查您是否已經有現有的 SSH Key：

```bash
ls -al ~/.ssh
```

如果您看到類似 `id_rsa.pub`、`id_ed25519.pub` 等檔案，表示您已經有 SSH Key。

### 2. 生成新的 SSH Key

為不同的服務或帳戶生成不同的 SSH Key：

```bash
# 為 GitHub 生成 SSH Key
ssh-keygen -t ed25519 -C "your-email@example.com" -f ~/.ssh/id_ed25519_github

# 為 GitLab 生成 SSH Key
ssh-keygen -t ed25519 -C "your-email@example.com" -f ~/.ssh/id_ed25519_gitlab

# 為公司的 Git 服務生成 SSH Key
ssh-keygen -t ed25519 -C "your-work-email@company.com" -f ~/.ssh/id_ed25519_company
```

**參數說明：**
- `-t ed25519`：指定加密類型（推薦使用 ed25519）
- `-C`：添加註釋，通常使用您的 email
- `-f`：指定 key 檔案的路徑和名稱

### 3. 設定檔案權限

確保 SSH Key 檔案的權限正確：

```bash
chmod 600 ~/.ssh/id_ed25519_*
chmod 644 ~/.ssh/id_ed25519_*.pub
```

## 設定多個 SSH Key

### 1. 將公鑰添加到各個服務

將對應的公鑰內容複製並添加到各個 Git 服務：

```bash
# 查看公鑰內容
cat ~/.ssh/id_ed25519_github.pub
cat ~/.ssh/id_ed25519_gitlab.pub
cat ~/.ssh/id_ed25519_company.pub
```

然後在各個服務的設定頁面添加相應的公鑰：
- **GitHub**: Settings → SSH and GPG keys → New SSH key
- **GitLab**: User Settings → SSH Keys → Add SSH Key
- **其他服務**: 查找相應的 SSH Key 設定選項

### 2. 啟動 SSH Agent

```bash
# 啟動 SSH Agent
eval "$(ssh-agent -s)"

# 將私鑰添加到 SSH Agent
ssh-add ~/.ssh/id_ed25519_github
ssh-add ~/.ssh/id_ed25519_gitlab
ssh-add ~/.ssh/id_ed25519_company
```

## 設定 SSH Config 檔案

創建或編輯 SSH 設定檔案來管理多個 SSH Key：

```bash
nano ~/.ssh/config
```

添加以下內容：

```
# GitHub 設定
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519_github
    IdentitiesOnly yes

# GitLab 設定
Host gitlab.com
    HostName gitlab.com
    User git
    IdentityFile ~/.ssh/id_ed25519_gitlab
    IdentitiesOnly yes

# 公司 Git 服務設定
Host git.company.com
    HostName git.company.com
    User git
    IdentityFile ~/.ssh/id_ed25519_company
    IdentitiesOnly yes

# 如果需要為同一服務使用不同帳戶，可以使用別名
Host github-work
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519_work
    IdentitiesOnly yes

Host github-personal
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519_personal
    IdentitiesOnly yes
```

**設定檔案權限：**

```bash
chmod 600 ~/.ssh/config
```

## 測試連接

測試每個 SSH Key 是否正確設定：

```bash
# 測試 GitHub 連接
ssh -T git@github.com

# 測試 GitLab 連接
ssh -T git@gitlab.com

# 測試公司 Git 服務連接
ssh -T git@git.company.com

# 測試別名連接
ssh -T git@github-work
ssh -T git@github-personal
```

成功的連接應該會顯示類似以下的訊息：
```
Hi username! You've successfully authenticated, but GitHub does not provide shell access.
```

## 使用不同的 SSH Key 克隆倉庫

根據您的 SSH config 設定，使用相應的主機名克隆倉庫：

```bash
# 使用 GitHub SSH Key 克隆
git clone git@github.com:username/repository.git

# 使用 GitLab SSH Key 克隆
git clone git@gitlab.com:username/repository.git

# 使用工作帳戶克隆 GitHub 倉庫
git clone git@github-work:company/repository.git

# 使用個人帳戶克隆 GitHub 倉庫
git clone git@github-personal:username/repository.git
```

## 為現有倉庫更改遠端 URL

如果您已經有本地倉庫，可以更改遠端 URL 來使用正確的 SSH Key：

```bash
# 查看當前遠端 URL
git remote -v

# 更改遠端 URL
git remote set-url origin git@github-work:company/repository.git
```

## 常見問題

### 1. Permission denied (publickey) 錯誤

**解決方法：**
- 確保公鑰已正確添加到 Git 服務
- 檢查 SSH Key 檔案權限
- 確認 SSH config 檔案設定正確
- 使用 `ssh -vT git@hostname` 進行詳細診斷

### 2. SSH Key 無法自動選擇

**解決方法：**
- 在 SSH config 中添加 `IdentitiesOnly yes`
- 確保 SSH Agent 正在運行並已添加正確的 key

### 3. 多個 GitHub 帳戶衝突

**解決方法：**
- 為每個帳戶創建不同的 SSH Key
- 在 SSH config 中使用別名（如 github-work、github-personal）
- 克隆或設定遠端時使用相應的別名

### 4. SSH Agent 重啟後 Key 消失

**解決方法：**
將以下內容添加到 `~/.bashrc` 或 `~/.zshrc`：

```bash
# 自動啟動 SSH Agent 並添加 Key
if [ -z "$SSH_AUTH_SOCK" ]; then
    eval "$(ssh-agent -s)"
    ssh-add ~/.ssh/id_ed25519_github
    ssh-add ~/.ssh/id_ed25519_gitlab
    ssh-add ~/.ssh/id_ed25519_company
fi
```

### 5. 檢查當前使用的 SSH Key

```bash
# 查看已添加到 SSH Agent 的 Key
ssh-add -l

# 詳細檢查連接使用的 Key
ssh -vT git@github.com
```

## 安全建議

1. **定期輪換 SSH Key**: 建議每年更新一次 SSH Key
2. **為不同用途使用不同的 Key**: 工作和個人使用分開的 Key
3. **備份您的 SSH Key**: 將 Key 備份到安全的位置
4. **使用強密碼保護私鑰**: 在生成 Key 時設定密碼短語
5. **監控 SSH Key 使用情況**: 定期檢查各服務的 SSH Key 活動日誌

## 結論

通過正確設定多個 SSH Key，您可以安全高效地管理多個 Git 倉庫的訪問。記住定期檢查和更新您的 SSH Key 設定，確保安全性和功能性。

如有任何問題，請參考各 Git 服務的官方文檔或尋求技術支援。
