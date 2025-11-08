#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace ast {

using namespace rapidjson;

// ---------- Node AST ----------

struct Node {
    std::string type;
    std::map<std::string, std::string> props;
    std::vector<Node> children;
};

// ---------- Basic ----------

inline Node element(
    const std::string& type,
    std::vector<Node> children = {},
    std::map<std::string, std::string> props = {}
) {
    return Node{type, std::move(props), std::move(children)};
}

inline Node text(const std::string& value) {
    return Node{"#text", {{"value", value}}, {}};
}

// ---------- Macros ----------

#define TAG(name) \
inline Node name(std::vector<Node> children = {}, \
                 std::map<std::string, std::string> props = {}) { \
    return element(#name, std::move(children), std::move(props)); \
}

// ---------- basic HTML tags ----------

TAG(div)
TAG(span)
TAG(p)
TAG(h1)
TAG(h2)
TAG(h3)
TAG(h4)
TAG(h5)
TAG(h6)
TAG(ul)
TAG(ol)
TAG(li)
TAG(table)
TAG(thead)
TAG(tbody)
TAG(tr)
TAG(td)
TAG(th)
TAG(img)
TAG(a)
TAG(button)
TAG(input)
TAG(label)
TAG(form)
TAG(select)
TAG(option)
TAG(canvas)
TAG(section)
TAG(article)
TAG(header)
TAG(footer)
TAG(main)
TAG(nav)
TAG(video)
TAG(audio)
TAG(svg)
TAG(path)
TAG(rect)
TAG(circle)
TAG(line)
TAG(g)

// ---------- Recharts tags ----------

TAG(ResponsiveContainer)
TAG(LineChart)
TAG(BarChart)
TAG(PieChart)
TAG(AreaChart)
TAG(XAxis)
TAG(YAxis)
TAG(ZAxis)
TAG(Tooltip)
TAG(Legend)
TAG(Line)
TAG(Bar)
TAG(Pie)
TAG(Area)
TAG(Cell)
TAG(CartesianGrid)
TAG(Brush)
TAG(ReferenceLine)
TAG(ReferenceDot)
TAG(ComposedChart)
TAG(ScatterChart)
TAG(Scatter)
TAG(RadarChart)
TAG(Radar)
TAG(PolarGrid)
TAG(PolarAngleAxis)
TAG(PolarRadiusAxis)

// ---------- Props helper ----------

inline std::map<std::string, std::string> props(
    std::initializer_list<std::pair<const std::string, std::string>> kv
) {
    return std::map<std::string, std::string>(kv);
}

// ---------- JSON сериализация ----------

inline void to_json(const Node& node, Value& out, Document::AllocatorType& alloc) {
    out.SetObject();
    out.AddMember("type", Value(node.type.c_str(), alloc), alloc);

    // props
    if (!node.props.empty()) {
        Value propsObj(kObjectType);
        for (auto& [k, v] : node.props)
            propsObj.AddMember(Value(k.c_str(), alloc), Value(v.c_str(), alloc), alloc);
        out.AddMember("props", propsObj, alloc);
    }

    // children
    if (!node.children.empty()) {
        Value childrenArr(kArrayType);
        for (auto& c : node.children) {
            Value child(kObjectType);
            to_json(c, child, alloc);
            childrenArr.PushBack(child, alloc);
        }
        out.AddMember("children", childrenArr, alloc);
    }
}

// ---------- Stringify helper ----------

inline std::string stringify(const Node& node) {
    Document doc;
    auto& alloc = doc.GetAllocator();
    Value root(kObjectType);
    to_json(node, root, alloc);
    doc.Swap(root);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    return buffer.GetString();
}

// ---------- utils none() ----------

inline std::vector<Node> none() { return {}; }

} // namespace ast
