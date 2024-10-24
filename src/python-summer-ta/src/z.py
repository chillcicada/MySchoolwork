import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report
from chemdataextractor import Document
from pdfminer.high_level import extract_text
import re
import logging
# from sklearn.metrics import classification_report

# 设置日志记录
logging.basicConfig(level=logging.INFO)

# 读取标注好的数据集
data = pd.read_csv(r'C:\Users\Lenovo\Desktop\chemical_石墨烯chapter1.csv')


# 函数：使用chemdataextractor提取化学物质名称
def extract_chemicals(pdf_path):
    try:
        text = extract_text(pdf_path)
        text = re.sub(r'\d+\s+of\s+\d+', '', text)  # 去除页码
        text = re.sub(r'\d+\s+\(.*?\)', '', text)  # 去除页码和版权声明
        text = re.sub(r'\d+–\d+', '', text)  # 去除范围数字
        text = re.sub(r'© 2024', '', text)  # 去除版权声明
        text = re.sub(r'No\. \d+', '', text)  # 去除编号
        doc = Document.from_string(text.encode('utf-8'))
        chemicals = [str(compound) for compound in doc.cems if hasattr(compound, 'names')]
        return ' '.join(chemicals)
    except Exception as e:
        logging.error(f'Error extracting chemicals from {pdf_path}: {e}')
        return ''


# 使用TF-IDF向量化化学物质名称
vectorizer = TfidfVectorizer(stop_words='english')
X = vectorizer.fit_transform(data['Chemical Compound'])
y = data['Chemical Compound']

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 训练随机森林分类器
model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# 评估模型
y_pred = model.predict(X_test)
print(classification_report(y_test, y_pred, zero_division=1))


# 模型应用到新的PDF文档来提取化学物质名称
def predict_chemicals(pdf_path):
    chemicals = extract_chemicals(pdf_path)
    X_new = vectorizer.transform([chemicals])
    predictions = model.predict(X_new)
    return predictions


# 这里就是应用到了标记出数据集的PDF文档
new_pdf_path = r'C:\Users\Lenovo\Desktop\石墨烯chapter1.pdf'
predicted_chemicals = predict_chemicals(new_pdf_path)
print(predicted_chemicals)
