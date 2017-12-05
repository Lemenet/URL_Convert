# URL_Convert
网址URL转换器，将被搜索引擎包裹的实际搜索网址解析出来

我在公司的外网限流，登录虚幻官网查询资料时，点击搜索结果会跳转Bing搜索，然后从Bing跳转到目的网址。但是公司的网限制了Bing的跳转，导致搜索结果正确打开。
这个程序是为了去除Bing搜索相关的字符，还原出目的网址原本的内容。

使用时将网址填在原网址中，根据网址结尾是html还是&p等字符确定网址结尾，程序会自动寻找http开头和对应结尾。
目前暂时不能手动添加其他的网址结尾，只有默认的html和&p两个可选项。
