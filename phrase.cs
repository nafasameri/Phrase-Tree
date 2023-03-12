using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tree
{
    class phrase
    {
        public string intpre(string In)
        {
            stack s = new stack();
            stack k = new stack();
            int j = In.Length;
            //for (j = 0; In[j]; j++);
            for (int i = j - 1; i >= 0; i--)
            {
                if (In[i] == '*' || In[i] == '/')
                    s.push(In[i].ToString());

                else if (In[i] == '+' || In[i] == '-')
                {
                    int flag = 0;
                    while (flag == 0 && !s.isempty())
                    {
                        string c = s.pop();
                        if (c == "+" || c == "-")
                        {
                            s.push(c);
                            flag = 1;
                        }
                        else
                            k.push(c);
                    }
                    s.push(In[i].ToString());
                }
                else
                    k.push(In[i].ToString());

            }
            while (!s.isempty())
                k.push(s.pop());

            string temp = "";
            while (!k.isempty())
                temp += k.pop();
            return temp;
        }

        public string valupre(string pre)
        {
            stack s = new stack();
            int x;
            int j = pre.Length;
            //for (j = 0; pre[j]; j++) ;
            for (int i = j - 1; i >= 0; i--)
            {
                //if (pre[i] - '0' >= 0 && pre[i] - '0' <= 9)
                //{
                //    pre[i] = pre[i] - '0';
                //    s.push(pre[i]);
                //}
                if(isDigit(pre[i]))
                {
                    s.push(pre[i].ToString());
                }
                else
                {
                    int op1, op2;
                    try
                    {
                        op1 = Convert.ToInt32(s.pop());
                        op2 = Convert.ToInt32(s.pop());
                    }
                    catch
                    {
                        op1 = 0;
                        op2 = 0;
                    }
                    switch (pre[i])
                    {
                        case '+':
                            x = op1 + op2;
                            s.push(x.ToString());
                            break;

                        case '-':
                            x = op1 - op2;
                            s.push(x.ToString());
                            break;

                        case '*':
                            x = op1 * op2;
                            s.push(x.ToString());
                            break;

                        case '/':
                            x = op1 / op2;
                            s.push(x.ToString());
                            break;
                    }
                }
            }
            //x = s.pop();
            //cout << x;
            return s.pop();
        }

        public string intopost(string In)
        {
            string temp = "";
            stack s = new stack();
            for (int i = 0; i < In.Length; i++)
            {
                //if (In[i] - 48 >= 0 && In[i] - 48 <= 99)
                if (isDigit(In[i])) 
                {
                    temp += In[i].ToString();
                    //cout << in[i];
                }
                else if (In[i] == '*' || In[i] == '/')
                    s.push(In[i].ToString());
                else if (In[i] == '+' || In[i] == '-')
                {
                    while (!s.isempty())
                        temp += s.pop();
                        //cout << s.pop();
                    s.push(In[i].ToString());
                }

            }
            while (!s.isempty())
                temp += s.pop();
            //cout << s.pop();
            return temp;
        }

        public string valpost(string post)
        {
            stack s = new stack();
            int x;
            for (int i = 0; i < post.Length; i++)
            {
                //if (post[i] - 48 >= 0 && post[i] - 48 <= 99)
                //{
                //    post[i] = post[i] - 48;
                //    s.push(post[i].ToString());
                //}
                if (isDigit(post[i]))
                    s.push(post[i].ToString());
                else
                {
                    int op1, op2;
                    try
                    {
                        op2 = Convert.ToInt32(s.pop());
                        op1 = Convert.ToInt32(s.pop());
                    }
                    catch
                    {
                        op1 = 0;
                        op2 = 0;
                    }
                    switch (post[i])
                    {
                        case '+':
                            x = op1 + op2;
                            s.push(x.ToString());
                            break;
                        case '-':
                            x = op1 - op2;
                            s.push(x.ToString());
                            break;
                        case '*':
                            x = op1 * op2;
                            s.push(x.ToString());
                            break;
                        case '/':
                            x = op1 / op2;
                            s.push(x.ToString());
                            break;
                    }

                }
            }
            //x = s.pop();
            //cout << x;
            return s.pop();
        }

        public string posttoin(string post)
        {
            string temp = "";
            stack s = new stack();
            for (int i = 0; i < post.Length; i++)
            {
                if (isDigit(post[i]))
                    s.push(post[i].ToString());
                else if(!isDigit(post[i]))
                {
                    string str1 = s.pop();
                    string str2 = s.pop();
                    string str = '(' + str2 + post[i] + str1 + ')';
                    s.push(str);
                }
            }
            while (!s.isempty())
                temp += s.pop();
            return temp;
        }

        public bool isDigit(char c)
        {
            return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9';
        }

        public bool isoperand(char c)
        {
            return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
        }
    

        public node intotree(string In)
        {
            node root = new node();
            node p = root;
            //char h;
            for (int i = 0; i < In.Length - 1; i++)
            {
                if (In[i] == '(')
                {
                    p.lch = new node(0, null, null, p);
                    p = p.lch;
                }
                else if (isoperand(In[i]))
                {
                    p.data = In[i];
                    p = p.parent;
                }
                else if (In[i] == ')')
                {
                    p = p.parent;
                }
                else if (isDigit(In[i]))
                {
                    p.data = In[i];
                    p.rch = new node(0, null, null, p);
                    p = p.rch;
                }
            }
            return p;
        }
        public node pparent(node r, node parent, int x)
        {
            //friend node intotree(in[]);
            if (r == null) return null;
            else if (r.data == x)
                return parent;
            else
            {
                node mn = pparent(r.lch, r, x);
                if (mn != null)
                    return mn;
                else return pparent(r.rch, r, x);
            }

        }
        public node posttotree(string p)
        {
            node m = null;
            //if (j >= 0)
            //{
            //    m = new node(p[j]);
            //    if (isoperand(p[j]))
            //    {
            //        j--;
            //        m.rch = posttotree(p, ref j);
            //        m.lch = posttotree(p, ref j);
            //    }
            //}

            //return m;

            node h = m;
            bool flag = false;
            for (int i = 0; i < p.Length; i++)
            {
                if (isoperand(p[i]))
                    m.data = p[i];
                else if (isDigit(p[i]))
                    if (flag == false)
                    {
                        m.lch = new node(p[i]);
                        m = m.lch;
                        flag = true;
                    }
                    else if (flag == true)
                    {
                        m.rch = new node(p[i]);
                        m = m.rch;
                        flag = false;
                    }
            }
            return m;
        }
    }
}
