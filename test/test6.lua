function test6()
    print("test6")
    local t = test.Test:new()
    t.onend = function(self)
        if self.ondone then
           print("û��ʵ��ondone")
        end
    end
    t:play()
end
