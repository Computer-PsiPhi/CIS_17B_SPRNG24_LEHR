

const validation = new JustValidate("#signup");

validation
        .addField ("#name",[
          {
          rule: "required"      
          }
         ])
          .addField ("#email",[
          {
          rule: "required"      
          },
          {
              rule:"email"
          }
        
         ]);