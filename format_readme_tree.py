import os
import re


# get all README.md
def allPath(dirname):
    result = []
    for root, dirs, files in os.walk(dirname):
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for filename in files:
            if filename.endswith(('md')):
                apath = os.path.join(root, filename)
                result.append(apath)
    # remove current README.md
    result.remove('./README.md')
    return result


# get README.md title
def getReadmeContent(file, title):
    data = ""
    file_source = ""
    with open(file, "r", encoding="utf-8") as f:
        file_source += f.read()
    # match # title all-line until hit # or \Z
    it = re.finditer(
        r"^#\s"+title+"((?:\n+.+)*?)(?=(?:\n+#|\Z))", file_source.strip(), re.M)
    for match in it:
        data = match.group(1).strip()
    return data


# format files dict
def formatFiles(readme_files, title="name"):
    data = {}
    for file in readme_files:
        content = getReadmeContent(file, title)
        if content == "":
            continue
        url_cuts = file.split('/')
        url_path = [i for i in url_cuts if i not in ['.', 'README.md']]
        if url_cuts[1] not in data:
            data[url_cuts[1]] = []
        data[url_cuts[1]].append("["+content+"]("+"/".join(url_path)+")")
    return data


# example: {2020: [], 2021: {01: []}}
def iterdict(d, span=''):
    data = ""
    for k, val in d.items():
        data += span+" * "+k+"\n"
        if isinstance(val, dict):
            iterdict(val, span+'\t')
        elif isinstance(val, list):
            for v in val:
                data += span+'\t'+' * '+v+"\n"
        else:
            data += span+" * "+v+"\n"
    return data


# replace main README.md
def replaceFile(new_content, file="./README.md", title="directory"):
    old_source = ""
    with open(file, "r", encoding="utf-8") as f:
        old_source += f.read()
    content = getReadmeContent(file, title)
    new_source = old_source.strip().replace(content, new_content, 1)
    with open(file, "w", encoding="utf-8") as f:
        f.write(new_source)
    print("done")


readme_files = allPath(".")
readme_files.sort(reverse=True)
readme_lists = formatFiles(readme_files)
readme_source = iterdict(readme_lists)
replaceFile(readme_source)
